#include "dbg.h"
#include "mod.h"

const char* MY_NAME = "Max Lell";

int main(void) {
  log_info("My name: %s, age %d", MY_NAME, get_age());
  set_age(100);
  log_info("My name: %s, age %d", MY_NAME, get_age());

  log_info("THE_SIZE is %d", THE_SIZE);

  THE_SIZE = 9;

  log_info("THE_SIZE is %d", THE_SIZE);
  print_size();

  log_info("ratio at 1st: %f", update_ratio(123.0));
  log_info("ratio at 2nd: %f", update_ratio(19.0));
  log_info("ratio at 3rd: %f", update_ratio(200.0));

  run_recursive_function_forever(1);

  return 0;
}