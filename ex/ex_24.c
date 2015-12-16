#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EYE_COLOR
{
  BLUE_EYES,
  GREEN_EYES,
  BROWN_EYES,
  BLACK_EYES,
  OTHER_EYES
} EYE_COLOR;

const char *EYE_COLOR_NAMES[] =
{
  "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct person
{
  int age;
  char first_name[MAX_DATA];
  char last_name [MAX_DATA];
  EYE_COLOR eyes;
  float income;
} person;

/* remove new empty space and \n */
void string_trunc(char *str, int len)
{
  int i;
  /* skip empty space and \n */
  for(i = len - 1; isspace(str[i]); --i)
    ;

  str[i + 1] = '\0';
}

int main()
{
  person you = { .age = 0 };
  
  char *in = NULL;
  printf("What's your first name? ");
  in = fgets(you.first_name, MAX_DATA - 1, stdin);
  check(in != NULL, "Failed to read first name.");
  string_trunc(you.first_name, strlen(you.first_name));

  in = NULL;
  printf("What's your last name? ");
  in = fgets(you.last_name, MAX_DATA - 1, stdin);
  check(in != NULL, "Failed to read last name.");
  string_trunc(you.last_name, strlen(you.last_name));

  in = NULL;
  char age_str[MAX_DATA];
  printf("How old are you? ");
  in = fgets(age_str, MAX_DATA - 1, stdin);  
  check(in != NULL, "Failed to read age.");
  you.age = atoi(age_str);
  check(you.age > 0, "Age must be a positiv number.");
  
  printf("What color are your eyes:\n");
  int i;
  for(i = 0; i <= OTHER_EYES; ++i)
    printf("%i) %s\n", i + 1, EYE_COLOR_NAMES[i]);
  printf("> ");

  in = NULL;
  char eyes_str[MAX_DATA];
  in = fgets(eyes_str, MAX_DATA - 1, stdin);
  check(in != NULL, "Failed to read eyes.");
  you.eyes = atoi(eyes_str) - 1;
  check(0 <= you.eyes && you.eyes <= OTHER_EYES, "Do it right, this is not a option.");

  in = NULL;
  char hour_str[MAX_DATA];
  printf("How mutch do you make an hour? ");
  in = fgets(hour_str, MAX_DATA - 1, stdin);
  check(in != NULL, "Failed to read hour.");
  you.income = atof(hour_str);

  printf("\n----RESULT----\n");
  printf("First name: %s\n", you.first_name);
  printf("Last name: %s\n", you.last_name);
  printf("Age: %i\n", you.age);
  printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
  printf("Income: %f\n", you.income);

  exit(EXIT_SUCCESS);
 error:
  exit(EXIT_FAILURE);
}
