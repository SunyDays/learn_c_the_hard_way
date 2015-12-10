#include <stdio.h>

int main(int argc, char **argv)
{
  if(argc != 2)
  {
    fprintf(stderr, "ERROR: you need one argument.\n");
    return 1;
  }

  int i;
  char letter;
  for(i = 0; argv[1][i] != '\0'; letter = argv[1][i++])
    switch(letter)
    {
      case 'a':
      case 'A':
	printf("%i: %c\n", i, letter);
	break;

      case 'e':
      case 'E':
	printf("%i: %c\n", i, letter);
	break;

      case 'i':
      case 'I':
	printf("%i: %c\n", i, letter);
	break;

      case 'o':
      case 'O':
	printf("%i: %c\n", i, letter);
	break;

      case 'u':
      case 'U':
	printf("%i: %c\n", i, letter);
	break;

      case 'y':
      case 'Y':
	if(i > 2)
	  printf("%i: %c\n", i, letter);
	break;

      default:
	printf("%i: %c is not a vowel\n", i, letter);
    }
  
  return 0;
}
