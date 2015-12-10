#include <stdio.h>

int main()
{
  int areas[] = {10, 12, 13, 14, 20};
  char name[] = "Zed";
  char full_name[] = {'Z', 'e', 'd', ' ', 'A', '.', ' ', 'S', 'h', 'a', 'w', '\0'};

  printf("Size of an int: %li\n", sizeof(int));
  printf("Size of areas (int[]): %li\n", sizeof(areas));
  printf("The number of ints in areas: %li\n", sizeof(areas) / sizeof(int));
  printf("The first area is %i, the 2nd %i.\n\n", areas[0], areas[1]);

  printf("The size of a char: %li\n", sizeof(char));
  printf("The size of name (char[]): %li\n", sizeof(name));
  printf("The number of chars: %li\n\n",sizeof(name) / sizeof(char));

  printf("The size of full_name (char[]): %li\n", sizeof(full_name));
  printf("The number of chars: %li\n\n",sizeof(full_name) / sizeof(char));

  printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);
  
  return 0;
}
