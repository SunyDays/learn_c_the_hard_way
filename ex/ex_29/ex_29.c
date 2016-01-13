#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "../dbg.h"

typedef int (*lib_function)(const char *data);

int main(int argc, char **argv)
{
  check(argc == 4, "USAGE: ex_29 ex_29_lib.so function data");

  char *lib_file = argv[1], *func_to_run = argv[2], *data = argv[3];

  void *lib = dlopen(lib_file, RTLD_NOW);
  check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());

  lib_function func = dlsym(lib, func_to_run);
  check(func != NULL, "Did not find %s function in the library %s: %s", func_to_run, lib_file, dlerror());

  int rc = func(data);
  check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);

  rc = dlclose(lib);
  check(rc == 0, "Failed to close %s", lib_file);

  exit(EXIT_SUCCESS);

 error:
  exit(EXIT_FAILURE);
}
