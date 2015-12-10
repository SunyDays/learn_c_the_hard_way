#include <stdlib.h>
#include <stdio.h>

struct stack
{
  int lenght;
  int *arr;
};

struct stack* stack_create()
{  
  struct stack *stk = malloc(sizeof(struct stack));
  stk->lenght = 0;

  return stk;
}

void stack_delete(struct stack *stk)
{
  free(stk->arr);
  free(stk);
}

void stack_push(struct stack *stk, int elem)
{  
  if(stk->lenght)
    stk->arr = realloc(stk->arr, (stk->lenght + 1) * sizeof(int));
  else
    stk->arr = malloc(sizeof(int));

  stk->arr[stk->lenght++] = elem;
}

void stack_pop(struct stack *stk, int *elem)
{
  if(stk->lenght)
  {
    *elem = stk->arr[--stk->lenght];
    stk->arr = realloc(stk->arr, stk->lenght * sizeof(int));
  }
  else
    elem = NULL;
}

void stack_print(struct stack *stk)
{
  printf("%i\n", stk->lenght);
  int i;
  for(i = 0; i < stk->lenght; ++i)
    printf("%i ", stk->arr[i]);
  printf("\n");
}

int main()
{
  struct stack *stk = stack_create();

  printf("PUSH\n");
  int i;
  for(i = 9; i >= 0; --i)
  {
    stack_push(stk, i);
    stack_print(stk);
  }

  printf("POP\n");
  do
  {
    stack_pop(stk, &i);
    stack_print(stk);
  } while(stk->lenght);
  
  stack_delete(stk);
  
  exit(EXIT_SUCCESS);
}
