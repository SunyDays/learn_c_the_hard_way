#include <stdlib.h>
#include <stdio.h>

/* #define NDEBUG */
#include "dbg.h"

void test_debug()
{
  debug("I have Brown Hair.");
  debug("I am %i years old.", 37);
}

void test_log_err()
{
  log_err("I believe everything is broken.");
  log_err("There are %i problems in %s.", 0, "space");
}

void test_log_warn()
{
  log_warn("You can safely ignore this.");
  log_warn("Maybe consider looking at: %s", "/etc/passwd");
}

void test_log_info()
{
  log_info("Well I did something mundane.");
  log_info("It happenes %f times today.", 1.3f);
}

int test_check(char *filename)
{
  FILE *input = NULL;
  char *block = NULL;

  block = malloc(100);
  check_mem(block);

  input = fopen(filename, "r");
  check(input, "Failed to open %s.", filename);

  free(block);
  fclose(input);
  return 0;

 error:
  if(block)
    free(block);
  if(input)
    fclose(input);
  return -1;
}

int test_sentinel(int code)
{
  char *temp = malloc(100);
  check_mem(temp);

  switch(code)
  {
    case 1:
      log_info("It worked.");
      break;
      
    default:
      sentinel("I shouldn't run.");
  }

  free(temp);
  return 0;

 error:
  if(temp)
    free(temp);
  return -1;
}

int test_check_mem()
{
  char *test = NULL;
  check_mem(test);

 error:
  return -1;
}

int test_check_debug()
{
  int i = 0;
  check_debug(i != 0, "Ooops, I was 0.");

  return 0;

 error:
  return -1;
}

int main(int argc, char **argv)
{
  check(argc == 2, "Need an argument.");

  test_debug();
  printf("--------------\n");
  test_log_err();
  printf("--------------\n");
  test_log_warn();
  printf("--------------\n");
  test_log_info();
  printf("--------------\n");

  check(test_check("ex_20/ex_20.c") == 0, "failed with ex_20.c");
  printf("--------------\n");
  check(test_check(argv[1]) == 0, "failed with argv");
  printf("--------------\n");
  check(test_sentinel(1) == 0, "test_sentinel failed");
  printf("--------------\n");
  check(test_sentinel(100) == -1, "test_sentinel failed");
  printf("--------------\n");
  check(test_check_mem() == -1, "test_check_mem failed");
  printf("--------------\n");
  check(test_check_debug() == -1, "test_check_debug failed");
  
  exit(EXIT_SUCCESS);

 error:
  exit(EXIT_FAILURE);
}
