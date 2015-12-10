#include <stdio.h>
#include <ctype.h>

void print_arguments(int argc, char **argv);
void print_letters(char *arg);
int can_print_it(char ch);

int main(int argc, char **argv)
{
  if(argc < 2)
  {
    fprintf(stderr, "ERROR: need at least one argument.\n");
    return 1;
  }
    
  print_arguments(argc, argv);
  
  return 0;
}

void print_arguments(int argc, char **argv)
{
  int i;
  for(i = 1; i < argc; ++i)
    print_letters(argv[i]);
}

void print_letters(char *arg)
{
  int i;
  for(i = 0; arg[i] != '\0'; ++i)
  {
    char ch = arg[i];
    if(can_print_it(ch))
      printf("'%c' = %i\n", ch, ch);
  }

  printf("\n");
}

int can_print_it(char ch)
{
  /* return isalpha(ch) || isblank(ch); */
    return isalpha(ch) || isspace(ch);
}
