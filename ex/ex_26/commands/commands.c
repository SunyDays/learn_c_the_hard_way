#include <apr_uri.h>
#include <apr_fnmatch.h>
#include <unistd.h>

#include "commands.h"
#include "../../dbg.h"
#include "../bstrlib/bstrlib.h"
#include "../db/db.h"
#include "../shell/shell.h"

int command_fetch(apr_pool_t *p, const char *url, int fetch_only)
{
  apr_uri_t info = { .port = 0 };
  int rc = 0;
  const char *depends_file = NULL;
  apr_status_t rv = apr_uri_parse(p, url, &info);
  check(rv == APR_SUCCESS, "Failed to parse URL: %s", url);

  if(apr_fnmatch(GIT_PAT, info.path, 0) == APR_SUCCESS)
  {
    rc = shell_exec(GIT_SH, "URL", url, NULL);
    check(rc == 0, "git failed.");
  }
  else if(apr_fnmatch(DEPEND_PAT, info.path, 0) == APR_SUCCESS)
  {
    check(!fetch_only, "No point in fetching a DEPENDS file.");

    if(info.scheme)
    {
      depends_file = DEPENDS_PATH;
      rc = shell_exec(WGET_SH, "URL", url, "TARGET", depends_file, NULL);
      check(rc == 0, "Wget failed.");
    }
    else
      depends_file = info.path;

    /* recursively process the devpkg list */
    log_info("Building according to DEPENDS: %s", url);
    rv = command_depends(p, depends_file);
    check(rv == 0, "Failed to process the DEPENDS: %s", url);
    
    return 0;
  }
  else if(apr_fnmatch(TAR_GZ_PAT, info.path, 0) == APR_SUCCESS)
  {
    if(info.scheme)
    {
      rc = shell_exec(WGET_SH, "URL", url, "TARGET", TAR_GZ_SRC, NULL);
      check(rc == 0, "Failed to wget source: %s", url);
    }

    rv = apr_dir_make_recursive(BUILD_DIR, APR_UREAD | APR_UWRITE | APR_UEXECUTE, p);
    check(rv == APR_SUCCESS, "Failed to make directory %s", BUILD_DIR);

    rc = shell_exec(TAR_SH, "FILE", TAR_GZ_SRC, NULL);
    check(rc == 0, "Failed to untar %s", TAR_GZ_SRC);
  }
  else if(apr_fnmatch(TAR_BZ2_PAT, info.path, 0) == APR_SUCCESS)
  {
    if(info.scheme)
    {
      rc = shell_exec(WGET_SH, "URL", url, "TARGET", TAR_BZ2_SRC, NULL);
      check(rc == 0, "Failed to wget source: %s", url);
    }

    rv = apr_dir_make_recursive(BUILD_DIR, APR_UREAD | APR_UWRITE | APR_UEXECUTE, p);
    check(rv == APR_SUCCESS, "Failed to make directory %s", BUILD_DIR);

    rc = shell_exec(TAR_SH, "FILE", TAR_BZ2_SRC, NULL);
    check(rc == 0, "Failed to untar %s", TAR_BZ2_SRC);
  }
  else
    sentinel("Don't know how to handle %s", url);
  
  return 1;

 error:
  return -1;
}

int command_install(apr_pool_t *p, const char *url, const char *configure_opts, const char *make_opts, const char *install_opts)
{
  int rc = 0;
  check(shell_exec(CLEANUP_SH, NULL) == 0, "Failed to cleanup before building.");

  rc = db_find(url);
  check(rc != -1, "Error checking the install database.");
  if(rc == 1)
  {
    log_info("Package %s already installed.", url);
    return 0;
  }  
  
  rc = command_fetch(p, url, 0);  
  if(rc == 1)
  {
    rc = command_build(p, url, configure_opts, make_opts, install_opts);
    check(rc == 0, "Failed to build: %s", url);
  }
  else if(rc == 0)
  {
    log_info("Depends successfully installed: %s", url);
  }
  else
    sentinel("Install failed: %s", url);
  
  shell_exec(CLEANUP_SH, NULL);
  return 0;

 error:
  shell_exec(CLEANUP_SH, NULL);
  return -1;
}

int command_depends(apr_pool_t *p, const char *path)
{
  FILE *in = fopen(path, "r");
  check(in != NULL, "Failed to open downloaded depends: %s", path);

  bstring line;
  for(line = bgets((bNgetc)fgetc, in, '\n'); line != NULL; line = bgets((bNgetc)fgetc, in, '\n'))
  {
    btrimws(line);
    log_info("Processing depends: %s", bdata(line));

    int rc = command_install(p, bdata(line), NULL, NULL, NULL);
    check(rc == 0, "Failed to install: %s", bdata(line));
    bdestroy(line);
  }

  fclose(in);
  return 0;

 error:
  if(line)
    bdestroy(line);
  if(in)
    fclose(in);
  return -1;
}

int command_build(apr_pool_t *p, const char *url, const char *configure_opts, const char *make_opts, const char *install_opts)
{
  int rc = 0;
  check(access(BUILD_DIR, X_OK | R_OK | W_OK) == 0, "Build directory doesn't exist: %s", BUILD_DIR);

  if(access(CONFIG_SCRIPT, X_OK) == 0)
  {
    log_info("Has a configure script, runnig it.");
    rc = shell_exec(CONFIGURE_SH, "OPTS", configure_opts, NULL);
    check(rc == 0, "Failed to configure.");
  }

  rc = shell_exec(MAKE_SH, "OPTS", make_opts, NULL);
  check(rc == 0, "Failed to build.");

  rc = shell_exec(INSTALL_SH, "TARGET", install_opts ? install_opts : "install", NULL);
  check(rc == 0, "Failed to install.");

  rc = shell_exec(CLEANUP_SH, NULL);
  check(rc == 0, "Failed to cleanup after build.");

  rc = db_update(url);
  check(rc == 0, "Failed to add this package to the database.");
  
  return 0;

 error:
  return -1;
}