#include "mod.h"

#include "dbg.h"
int THE_SIZE = 1000;

static int THE_AGE = 33;

int get_age() { return THE_AGE; }

void set_age(int age) { THE_AGE = age; }

void print_size() { log_info("I think the size is: %d", THE_SIZE); }

double update_ratio(double new_ratio) {
  /*
  Creates a new static variable in static memory
  The initialization of ratio is performed only
  once. "ratio" keeps its value

  These are rarely used in C due to the fact that they
  are hard to use with threads
  */
  static double ratio = 1.0;
  /*
  A local copy of ratio is created
  */
  double old_ratio = ratio;

  /*
  this is where the static variable is
  updated
  */
  ratio = new_ratio;

  return old_ratio;
}

void run_recursive_function_forever(int x) {
  while (1) {
    run_recursive_function_forever(x);
  }
}