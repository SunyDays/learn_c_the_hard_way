#include <stdio.h>

int main(int argc, char **argv)
{
  int i = 1;
  while(i < argc)
  {
    printf("arg %i: %s\n", i, argv[i]);
    ++i;
  }
  /* while(--argc) */
  /*   printf("arg %i: %s\n", argc, argv[argc]); */
  printf("\n");
  
  char *states[] = {"California", "Oregon", "Washington", "Texas"};
  int states_num = 4;

  i = 0;
  while(i < states_num)
  {
    printf("state %i: %s\n", i, states[i]);
    ++i;
  } 
  
  return 0;
}
