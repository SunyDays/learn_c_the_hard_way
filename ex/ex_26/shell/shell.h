#ifndef _shell_h
#define _shell_h

#define MAX_COMMAND_ARGS 100

#include <apr_thread_proc.h>

typedef struct shell
{
  const char *dir;
  const char *exe;

  apr_procattr_t *attr;
  apr_proc_t proc;
  apr_exit_why_e exit_why;
  int exit_code;

  const char *args[MAX_COMMAND_ARGS];
} shell;

int shell_run(apr_pool_t *p, shell *cmd);
int shell_exec(shell cmd, ...);

extern shell CLEANUP_SH;
extern shell GIT_SH;
extern shell TAR_SH;
extern shell WGET_SH;
extern shell CONFIGURE_SH;
extern shell MAKE_SH;
extern shell INSTALL_SH;

#endif
