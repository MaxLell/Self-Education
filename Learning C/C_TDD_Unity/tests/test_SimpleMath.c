/**
 * Simple Test Script for testing a bit of application Code
 */

#include <stdio.h>
#include <stdlib.h>
#include "../test_lib/unity.h"

/* ##########################################
          Test Source Code Includes
#############################################*/
#include "../ProductionCode/SimpleMath/SimpleMath.h"
#include "../ProductionCode/SimpleMath/SimpleMath_pow_helper.h"

/* ##########################################
              Test Setup
#############################################*/
void setUp(void)
{
  // set common stuff for all the tests up here.
}

void tearDown(void)
{
  // clean stuff up here after the test
}

/* ##########################################
              Test Functions
#############################################*/

static void test_IsOnePlusTwoEqualThree(void)
{
  /* Test Setup and preconditions */
  int32_t a = 1;
  int32_t b = 2;

  int32_t target = 3;

  /* Code-under-Test (CUT) function call */
  int32_t result = SimpleMath_add(a, b);

  /* Checking the results */
  TEST_ASSERT(result == target);
}

static void test_IsThreeTimesSevenEqual21(void)
{
  int32_t a = 3;
  int32_t b = 7;

  int32_t target = 21;

  int32_t result = SimpleMath_multiply(a, b);

  TEST_ASSERT(result == target);
}

#define ARRAY_SIZE 5
static void test_DoesPowWork(void)
{
  uint16_t input_array[ARRAY_SIZE] = {1, 2, 3, 4, 5};
  uint16_t output_array[ARRAY_SIZE] = {1, 4, 9, 16, 25};

  for (uint8_t i = 0; i < ARRAY_SIZE; i++)
  {
    uint32_t result = custom_pow(input_array[i]);
    TEST_ASSERT(result == output_array[i]);
  }
}

static void test_IsFancyFunctionWorking(void)
{
  uint16_t input = 2;
  uint16_t target = 6;

  uint32_t result = SimpleMath_fancyFunction(input);
  TEST_ASSERT(result == target);
}

/* ##########################################
              Test Runner
#############################################*/
int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_IsOnePlusTwoEqualThree);
  RUN_TEST(test_IsThreeTimesSevenEqual21);
  RUN_TEST(test_DoesPowWork);
  RUN_TEST(test_IsFancyFunctionWorking);

  return UNITY_END();
}
