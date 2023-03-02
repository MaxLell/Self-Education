#include <stdio.h>
#include <stdlib.h>

/*
 Helper function
*/
void print_line() { printf(" ----------------------- \n"); }

/*
What is a pointer exactly?
-> A pointer is nothing else but a memory address
*/
void what_is_a_pointer(void) {
  int a = 22;
  int *ptr = &a;
  printf("Address of ptr onto an int: %p\n", ptr);
  print_line();
}

/*
How to display the value behind the address stored in the pointer?
*/
void display_value_behind_address(void) {
  int a = 24;
  int *ptr = &a;
  int value = *ptr;
  printf("The [value]: %d behind [ptr]: %p\n", value, ptr);
  print_line();
}

/*
What does "**" mean?
-> See Obsidian
*/
void double_star_int() {
  int a = 10;
  int *simple_ptr = &a;
  printf("simple pointer address: %p\n", &simple_ptr);

  int **double_ptr = &simple_ptr;

  int value = **double_ptr;
  printf("value %d of the double ptr %p\n", value, double_ptr);
  print_line();
}

void double_star_char_array() {
  char *name_array[] = {"Max", "Sara", "Barbs"};
  printf("%s\n", name_array[1]);
  print_line();
}

void deallocate(void **ptr) {
  /*
  The function creates a local copy of the variable, that is passed to it.
  So in order to modify the pointer, yet another level of indirection needs
  to be introduced. The pointer itself needs to be transported as content.
  Content is mutable, the local copy of the function argument is not. This
  copy is trashed after a successful execution.
  */
  free(*ptr);
  *ptr = NULL;
}

void double_star_de_allocation() {
  int *memory = malloc(sizeof(int));
  printf("Address of [memory]:%p\n", memory);

  deallocate((void **)&memory);
  printf("Address of [memory]:%p\n", memory);
  print_line();
}

void null_the_address(void **ptr) { *ptr = NULL; }

void double_star_nulling() {
  int a = 12;
  int *first_stage_ptr_a = &a;
  printf("BEFORE: ptr address: %p\n", first_stage_ptr_a);

  int **sec_stage_ptr_a = &first_stage_ptr_a;
  null_the_address((void **)sec_stage_ptr_a);

  printf("AFTER : ptr address: %p\n", first_stage_ptr_a);

  print_line();
}

int main(void) {
  print_line();

  what_is_a_pointer();
  display_value_behind_address();
  double_star_int();
  double_star_de_allocation();
  double_star_char_array();
  double_star_nulling();
}