#include <stdlib.h>
#include "ex_22.h"
#include "../dbg.h"

const char *MY_NAME = "Zed A. Shaw";

void scope_demo(int count)
{
  log_info("count is: %i", count);

  if(count > 10)
  {
    int count = 100;
    log_info("count in this scope is: %i", count);
  }

  log_info("count is at exit: %i", count);
  count = 3000;
  log_info("count after assign: %i", count);
}

int main()
{
  log_info("My name: %s, age: %i", MY_NAME, get_age());

  set_age(100);
  log_info("My age is now: %i", get_age());

  log_info("THE_SIZE is: %i", THE_SIZE);
  print_size();

  THE_SIZE = 9;
  log_info("THE_SIZE is now: %i", THE_SIZE);
  print_size();

  log_info("Ratio at first: %f", update_ratio(2.0));
  log_info("Ratio again: %f", update_ratio(10.0));  
  log_info("Ratio once more: %f", update_ratio(300.0));

  int count = 4;
  scope_demo(count);
  scope_demo(count * 20);

  log_info("count after calling scope_demo: %i", count);
  
  exit(EXIT_SUCCESS);
}
