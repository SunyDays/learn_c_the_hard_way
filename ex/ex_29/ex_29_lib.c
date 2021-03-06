#include <stdio.h>
#include <ctype.h>
#include "../dbg.h"

int print_a_message(const char *msg)
{
  printf("A STRING: %s\n", msg);
  return 0;
}

int uppercase(int msg_len, const char *msg)
{
  int i;
  for(i = 0; i < msg_len; ++i)
    printf("%c", toupper(msg[i]));
  printf("\n");

  return 0;
}

int lowercase(int msg_len, const char *msg)  
{
  int i;
  for(i = 0; i < msg_len; ++i)
    printf("%c", tolower(msg[i]));
  printf("\n");

  return 0;
}

int fail_on_purpose(int msg_len, const char *msg)
{
  return 1;
}
