#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100

int read_string(char **out_string, int max_buffer)
{
  *out_string = calloc(1, max_buffer + 1);
  check_mem(*out_string);

  char *result = fgets(*out_string, max_buffer, stdin);
  check(result != NULL, "Input error.");

  return 0;
  
 error:
  if(*out_string)
    free(*out_string);
  return -1;
}

int read_int(int *out_int)
{
  char *input = NULL;
  int rc = read_string(&input, MAX_DATA);
  check(rc == 0, "Failed to read number.");

  *out_int = atoi(input);

  free(input);
  return 0;

 error:
  if(input)
    free(input);
  return -1;
}

int read_scan(const char *fmt, ...)
{
  int i, rc = 0, *out_int = NULL, max_buffer = 0;
  char *out_char = NULL, **out_string = NULL;

  va_list argp;
  va_start(argp, fmt);

  for(i = 0; fmt[i] != '\0'; ++i)
  {
    if(fmt[i] == '%')
    {
      ++i;
      switch(fmt[i])
      {
        case '\0':
	  sentinel("Invalid format, you ended with %%.");
	  break;

        case 'd':
        case 'i':
	  out_int = va_arg(argp, int*);
	  rc = read_int(out_int);
	  check(rc == 0, "Failed to read int.");
	  break;

        case 'c':
	  out_char = va_arg(argp, char*);
	  *out_char = fgetc(stdin);	  
	  break;

        case 's':
	  max_buffer = va_arg(argp, int);
	  out_string = va_arg(argp, char**);
	  rc = read_string(out_string, max_buffer);
	  check(rc == 0, "Failed to read string.");
	  break;

        default:
	  sentinel("Invalid format.");
      }
    }
    else
      fgetc(stdin);

    check(!feof(stdin) && !ferror(stdin), "Input error.");
  }

  va_end(argp);
  return 0;

 error:
  va_end(argp);
  return -1;
}

int main()
{
  char *first_name = NULL, *last_name = NULL, initial = ' ';
  int age = 0;

  printf("What's your first name? ");
  int rc = read_scan("%s", MAX_DATA, &first_name);
  check(rc == 0, "Failed first name.");

  printf("What's your initial? ");
  rc = read_scan("%c\n", &initial);
  check(rc == 0, "Failed initial.");

  printf("What's your last name? ");
  rc = read_scan("%s", MAX_DATA, &last_name);
  check(rc == 0, "Failed last name.");

  printf("How old are you? ");
  rc = read_scan("%i", &age);

  printf("\n----RESULT----\n");
  printf("First name: %s\n", first_name);
  printf("Initial: '%c'\n", initial);
  printf("Last name: %s\n", last_name);
  printf("Age: %i\n", age);

  free(first_name);
  free(last_name);
  exit(EXIT_SUCCESS);

 error:
  exit(EXIT_FAILURE);
}
