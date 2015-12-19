#include <stdarg.h>
#include "shell.h"
#include "../../dbg.h"

int shell_exec(shell template, ...)
{
  int rc = -1;
  apr_pool_t *p = NULL;

  apr_status_t rv = apr_pool_create(&p, NULL);
  check(rv == APR_SUCCESS, "Failed to create pool.");

  va_list argp;
  va_start(argp, template);

  const char *key, *arg;
  for(key = va_arg(argp, const char*); key != NULL; key = va_arg(argp, const char*))
  {
    arg = va_arg(argp, const char*);
    
    int i;
    for(i = 0; template.args[i] != NULL; ++i)
      if(strcmp(template.args[i], key) == 0)
      {
	template.args[i] = arg;
	break;
      }
  }

  rc = shell_run(p, &template);
  apr_pool_destroy(p);
  va_end(argp);
  return rc;

 error:
  if(p)
    apr_pool_destroy(p);
  return rc;
}

int shell_run(apr_pool_t *p, shell *cmd)
{
  apr_procattr_t *attr;
  apr_status_t rv = apr_procattr_create(&attr, p);
  check(rv == APR_SUCCESS, "Failed to create proc attr.");

  rv = apr_procattr_io_set(attr, APR_NO_PIPE, APR_NO_PIPE, APR_NO_PIPE);
  check(rv == APR_SUCCESS, "Failed to set IO of command.");

  rv = apr_procattr_dir_set(attr, cmd->dir);
  check(rv == APR_SUCCESS, "");

  rv = apr_procattr_cmdtype_set(attr, APR_PROGRAM_PATH);
  check(rv == APR_SUCCESS, "Failed to set cmd type.");

  apr_proc_t newproc;
  rv = apr_proc_create(&newproc, cmd->exe, cmd->args, NULL, attr, p);
  check(rv == APR_SUCCESS, "Failed to run command.");

  rv = apr_proc_wait(&newproc, &cmd->exit_code, &cmd->exit_why, APR_WAIT);
  check(rv == APR_CHILD_DONE, "Failed to wait.");

  check(cmd->exit_code == 0, "%s exited badly.", cmd->exe);
  check(cmd->exit_why == APR_PROC_EXIT, "%s was killed or crashed.", cmd->exe);
  
  return 0;

 error:
  return -1;
}

shell CLEANUP_SH =
{
  .exe = "rm",
  .dir = "/tmp",
  .args = {"rm", "-rf", "/tmp/pkg-build", "/tmp/pkg-src.tar.gz", "/tmp/pkg-src.tar.bz2", "/tmp/DEPENDS", NULL}
};

shell GIT_SH =
{
  .exe = "git",
  .dir = "/tmp",
  .args = {"git", "clone", "URL", "pkg-build", NULL}
};

shell TAR_SH =
{
  .exe = "tar",
  .dir = "/tmp/pkg-build",
  .args = {"tar", "-xzf", "FILE", "--strip-components", "1", NULL}
};

shell WGET_SH =
{
  .exe = "wget",
  .dir = "/tmp",
  .args = {"wget", "URL", NULL}
};

shell CONFIGURE_SH =
{
  .exe = "./configure",
  .dir = "/tmp/pkg-build",
  .args = {"configure", "OPTS", NULL}
};

shell MAKE_SH =
{
  .exe = "make",
  .dir = "/tmp/pkg-build",
  .args = {"make", "OPTS", NULL}
};

shell INSTALL_SH =
{
  .exe = "sudo",
  .dir = "/tmp/pkg-build",
  .args = {"sudo", "make", "TARGET", NULL}
};
