#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char *message)
{
  if(errno)
    perror(message);
  else
    fprintf(stderr, "ERROR: %s.\n", message);

  exit(EXIT_FAILURE);
}

typedef int (*compare_cb)(int a, int b);

int* bubble_sort(int *numbers, int count, compare_cb cmp)
{
  int temp, i, j;
  int *target = malloc(count * sizeof(int));
  if(!target)
    die("Memmory error");

  memcpy(target, numbers, count * sizeof(int));

  for(i = 0; i < count; ++i)
    for(j = 0; j < count - 1; ++j)
      if(cmp(target[j], target[j + 1]) > 0)
      {
	temp = target[j + 1];
	target[j + 1] = target[j];
	target[j] = temp;
      }

  return target;
}

int sorted_order(int a, int b)
{
  return a - b;
}

int reverse_order(int a, int b)
{
  return b - a;
}

int strange_order(int a, int b)
{
  if(a == 0 || b == 0)
    return 0;
  else
    return a % b;
}

void test_sorting(int *numbers, int count, compare_cb cmp)
{
  int *sorted = bubble_sort(numbers, count, cmp);

  if(!sorted)
    die("Failed to sort as requested");

  int i;
  for(i = 0; i < count; ++i)
    printf("%i ", sorted[i]);
  printf("\n");

  free(sorted);
}

int main(int argc, char **argv)
{
  if(argc < 2)
    die("USAGE: ex_18 4 3 1 5 6");

  int count = argc - 1, i;
  char **inputs = &argv[1];
  int *numbers = malloc(count * sizeof(int));
  if(!numbers)
    die("Memory error");

  for(i = 0; i < count; ++i)
    numbers[i] = atoi(inputs[i]);

  test_sorting(numbers, count, sorted_order);
  test_sorting(numbers, count, reverse_order);
  test_sorting(numbers, count, strange_order);

  free(numbers);
  exit(EXIT_SUCCESS);
}
