

#include "unity.h"
#include "Common.h"
#include "Bar.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * function shall return FAIL when the len is 0
 * function shall return OK when the len != 0
 */

void test_Bar_ArrayAdder_should_ReturnFail_when_LenEquals0(void)
{
    uint8_t len = 0;
    uint16_t inout_array[] = {};
    uint8_t status = Bar_ArrayAdder(inout_array, len);

    TEST_ASSERT_EQUAL(FAIL, status);
}

void test_Bar_ArrayAdder_should_ReturnOK_when_LenEqualsNotEqualZero(void)
{
    uint8_t len = 3;
    uint16_t inout_array[] = {2, 2, 3};
    uint8_t status = OK;
    status = Bar_ArrayAdder(inout_array, len);
    TEST_ASSERT_EQUAL(OK, status);
}

uint32_t helper_AddAllArrayElement(uint16_t *inout_array, uint8_t len)
{
    uint32_t result = 0;
    for (uint8_t i = 0; i < len; i++)
    {
        result += inout_array[i];
    }
    return result;
}

void test_Bar_ArrayAdder_should_AddTheValuesOfTheProvidedArrayIntoItsFirstPosition_WhenValuesAreValid(void)
{
    uint8_t len = 3;
    uint16_t inout_array[] = {1, 2, 3};
    uint16_t target = 6;
    uint8_t status;
    status = Bar_ArrayAdder(inout_array, len);
    TEST_ASSERT_EQUAL(target, inout_array[0]);

    /* Introduction of a helper function for testing */
    len = 5;
    uint16_t inout_array_2[] = {22, 55, 4747, 1929, 179};
    target = helper_AddAllArrayElement(inout_array_2, len);
    status = Bar_ArrayAdder(inout_array_2, len);
    TEST_ASSERT_EQUAL(target, inout_array_2[0]);
}

/* Test the STATIC helper function */
extern uint8_t Bar_IsSumOutOfBounds(uint16_t *inout_array, uint16_t len);
void test_Bar_IsSumOutOfBounds_Return1_WhenSumOfValuesIsOutOfBounds(void)
{
    uint8_t len = 2;
    uint16_t inout_array[] = {0xFFFF, 0xFFFF};
    TEST_ASSERT_EQUAL(TRUE, Bar_IsSumOutOfBounds(inout_array, len));
}

void test_Bar_IsSumOutOfBounds_Return0_WhenSumOfValuesIsWithinBounds(void)
{
    uint8_t len = 2;
    uint16_t inout_array[] = {0x00FF, 0x00FF};
    TEST_ASSERT_EQUAL(FALSE, Bar_IsSumOutOfBounds(inout_array, len));
}

void test_Bar_ArrayAdder_should_ReturnStatusFailAndKeepTheArrayAsItWasBefore_WhenValuesGoOutOfBounds(void)
{
    uint8_t len = 2;
    uint16_t inout_array[] = {0xFFFF, 0xFFFF};
    uint16_t target_array[] = {0xFFFF, 0xFFFF};
    uint8_t status = FAIL;
    status = Bar_ArrayAdder(inout_array, len);
    TEST_ASSERT_EQUAL(0xFFFF, inout_array[0]);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(inout_array, target_array, len);
}
