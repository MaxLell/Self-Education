#include "Foo.h"

#include "Bar.h"
#include "Muz.h"

void Foo_init(void) { Muz_SetStatus(FAIL); }

/**
 * This function runs various operations on a
 * given array.
 */
STATIC void Foo_calc(uint16_t *inout_arr, uint8_t length) {
  /* Changes the arr */
  Bar_ArrayAdder(inout_arr, length);

  /* changes the array again ... */
  uint16_t a = inout_arr[0];
  for (uint8_t i = 1; i < length; i++) {
    uint16_t b = inout_arr[i];
    uint16_t c = Muz_Subtractor(a, b);
    inout_arr[i] = c;
  }
}

uint8_t Foo_exec(Foo_Data_t *foo_data) {
  Foo_calc(foo_data->array, foo_data->len);

  return (OK);
}