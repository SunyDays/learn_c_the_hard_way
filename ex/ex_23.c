#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dbg.h"

int normal_copy(char *from, char *to, int count)
{
  int i;
  for(i = 0; i < count; ++i)
    to[i] = from[i];

  return i;
}

int duffs_device(char *from, char *to, int count)
{
  {
    int n = (count + 7) / 8;

    switch(count % 8)
    {
      case 0:
	do
	{
	  *to++ = *from++;

	  case 7: *to++ = *from++;
	  case 6: *to++ = *from++;
	  case 5: *to++ = *from++;
	  case 4: *to++ = *from++;
	  case 3: *to++ = *from++;
	  case 2: *to++ = *from++;
	  case 1: *to++ = *from++;
	} while(--n > 0);
    }
  }

  return count;
}

int zeds_device(char *from, char *to, int count)
{
  {
    int n = (count + 7) / 8;

    switch(count % 8)
    {
      case 0:
        again: *to++ = *from++;

      case 7: *to++ = *from++;
      case 6: *to++ = *from++;
      case 5: *to++ = *from++;
      case 4: *to++ = *from++;
      case 3: *to++ = *from++;
      case 2: *to++ = *from++;
      case 1: *to++ = *from++;
	if(--n > 0) goto again;
    }
  }

  return count;
}

int valid_copy(char *data, int count, char expects)
{
  int i;
  for(i = 0; i < count; ++i)
    if(data[i] != expects)
    {
      log_err("[%i] %c != %c", i, data[i], expects);
      return 0;
    }

  return 1;
}
  
int main()
{
  int n = 1000;
  char from[n], to[n];
  int rc = 0;

  memset(from, 'x', n);
  memset(to, 'y', n);
  check(valid_copy(to, n, 'y'), "Not initialized right.");
  printf("-------------\n");
  
  rc = normal_copy(from, to, n);
  check(rc == n, "Normal copy failed: %i", rc);
  check(valid_copy(to, n, 'x'), "Normal copy failed.");
  printf("-------------\n");

  memset(to, 'y', n);

  rc = duffs_device(from, to, n); 
  check(rc == n, "Duff's device failed: %i", rc);
  check(valid_copy(to, n, 'x'), "Duff's device failed copy.");
  printf("-------------\n");

  memset(to, 'y', n);

  rc = zeds_device(from, to, n); 
  check(rc == n, "Zed's device failed: %i", rc);
  check(valid_copy(to, n, 'x'), "Zed's device failed copy.");
  
  exit(EXIT_SUCCESS);
 error:
  exit(EXIT_FAILURE);
}
