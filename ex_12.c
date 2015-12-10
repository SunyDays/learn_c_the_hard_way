#include <stdio.h>

int main(int argc, char **argv)
{
  if(argc == 1)
    printf("You have no argument. You suck.\n");
  else if(argc > 1 && argc < 4)
  {
    printf("Here is your arguments:\n");

    int i;
    for(i = 1; i < argc; ++i)
      printf("\t%s\n", argv[i]);
  }
  else
    printf("You have too many arguments. You suck.\n");    
  
  return 0;
}
