#include "SimpleMath.h"
#include "SimpleMath_pow_helper.h"

int32_t SimpleMath_add(int32_t a, int32_t b)
{
  int32_t c = a + b;
  return c;
}

int32_t SimpleMath_multiply(int32_t a, int32_t b)
{
  return (a * b);
}

uint32_t SimpleMath_fancyFunction(uint16_t x)
{
  uint32_t tmp = custom_pow(x);
  tmp += x;
  return tmp;
}
