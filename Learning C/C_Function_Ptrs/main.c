#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbg.h"

/*
transforming the compare_callback function
to a typedef makes it possible to pass this
function as an argument to another function.

The type of this typedef is "compare_callback"
*/
typedef int (*compare_callback)(int a, int b);

int a_larger_b(int a, int b) {
  /*
  Tenery operator: c = (a > b) ? 1 : 0
  if   (a > b) then write c equals to one
  else c equals to 0
  */
  int c = ((a > b) ? 1 : 0);
  return c;
}

int b_larger_a(int a, int b) {
  int c = ((a > b) ? 0 : 1);
  return c;
}

int strange_stuff(int a, int b) {
  int c = a % b * 100;
  return (c > (b - a));
}

int* bubble_sort(int* unsorted_numbers, int len,
                 compare_callback compare_function) {
  int* sorted_numbers = malloc(len * sizeof(int));
  /*
  Creates a deep copy of the original numbers array
  This is an interesting case: an object from the stack
  is copied into an object of the heap.
  */
  memcpy(sorted_numbers, unsorted_numbers, (len) * sizeof(int));

  for (int step = 0; step < len - 1; step++) {
    for (int i = 0; i < len - step - 1; i++) {
      if (compare_function(sorted_numbers[i], sorted_numbers[i + 1])) {
        int tmp = sorted_numbers[i];
        sorted_numbers[i] = sorted_numbers[i + 1];
        sorted_numbers[i + 1] = tmp;
      }
    }
  }
  return sorted_numbers;
}

void print_array(int* arr, int len) {
  printf("[");
  for (int i = 0; i < len; i++) {
    printf("%d", arr[i]);
    if (i != len - 1) {
      printf(",");
    }
  }
  printf("]");
  printf("\n");
}

void test_sorting(int* numbers, int count) {
#define PRINT
#ifdef PRINT
  printf("Starting Array --------- : ");
  print_array(numbers, count);
  printf("\n");
#endif

  int* sorted_numbers = bubble_sort(numbers, count, a_larger_b);
#ifdef PRINT
  printf("Sorted (regular) Array - : ");
  print_array(sorted_numbers, count);
  printf("\n");
#endif

  sorted_numbers = bubble_sort(numbers, count, b_larger_a);
#ifdef PRINT
  printf("Sorted (reverse) Array - : ");
  print_array(sorted_numbers, count);
  printf("\n");
#endif

  sorted_numbers = bubble_sort(numbers, count, strange_stuff);
#ifdef PRINT
  printf("Sorted (strange) Array - : ");
  print_array(sorted_numbers, count);
  printf("\n");
#endif

  free(sorted_numbers);
}

int main(void) {
  // int numbers[] = {80, 1, 5, 6, 10, 93, 75, 8, 299, 98742, 6464};
  int numbers[] = {5, 1, 4, 2, 8, 10, 3, 13, 7};
  int count = sizeof(numbers) / sizeof(int);

  test_sorting(numbers, count);

  return 0;
}