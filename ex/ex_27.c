#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#undef NDEBUG
#include "dbg.h"

void copy(char to[], char from[])
{
  int i = 0;
  while((to[i] = from[i]) != '\0')
    ++i;
}

int safercopy(int to_len, char to[], int from_len, char from[])
{
  assert(to != NULL && from != NULL && "to and from can't be NULL");
  if(from_len < 0 || to_len <= 0) return -1;
  
  int max = to_len < from_len ? to_len - 1 : from_len;
  int i;
  
  for(i = 0; i < to_len; ++i)
    to[i] = i < max ? from[i] : '\0';
  
  return i;
}

int main()
{
  char from[] = "0123456789";
  int from_len = sizeof(from);

  char to[] = "0000";
  int to_len = sizeof(to);

  debug("Copying '%s':%d to '%s':%d", from, from_len, to, to_len);

  int rc = safercopy(to_len, to, from_len, from);
  check(rc > 0, "Failed to safercopy.");
  check(to[to_len - 1] == '\0', "String not terminated.");

  debug("Result is: '%s':%d", to, to_len);

  rc = safercopy(from_len * -1, from, to_len, to);
  check(rc == -1, "Safer copy should fail #1");
  check(to[to_len - 1] == '\0', "String not terminated.");

  rc = safercopy(from_len, from, 0, to);
  check(rc == -1, "Safer copy should fail #2");
  check(to[to_len - 1] == '\0', "String not terminated.");

  exit(EXIT_SUCCESS);

 error:
  exit(EXIT_FAILURE);
}
