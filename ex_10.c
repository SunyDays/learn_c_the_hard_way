#include <stdio.h>

int main(int argc, char **argv)
{
  int i;
  for(i = 1; i < argc; ++i)
    printf("arg %i: %s\n", i , argv[i]);
  printf("\n");

  char *states[] = {"California", "Oregon", "Washington", "Texas"};
  int states_num = 4;

  for(i = 0; i < states_num; ++i)
    printf("state %i: %s\n", i, states[i]);
  
  return 0;
}
