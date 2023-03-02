

#include "unity.h"

#include "Muz.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * White Box Tests
 */

/* Happy Day Testing */
extern uint8_t status_flag;
void test_Muz_Subtractor_should_NotRaiseAnErrorEvent_when_ResultIsGreaterZero(void)
{
    Muz_Subtractor(1, 0);
    TEST_ASSERT_EQUAL(OK, status_flag);

    Muz_Subtractor(100, 20);
    TEST_ASSERT_EQUAL(OK, status_flag);

    Muz_Subtractor(1299, 360);
    TEST_ASSERT_EQUAL(OK, status_flag);
}

void test_Muz_Subtractor_should_ReturnAValidResult(void)
{
    /* Lowest possible values */
    uint16_t a = 0;
    uint16_t b = 0;
    uint16_t target = a - b;
    uint16_t result = Muz_Subtractor(a, b);
    TEST_ASSERT_EQUAL(OK, status_flag);
    TEST_ASSERT_EQUAL(target, result);

    /* Mid Range Values */
    a = 23000;
    b = 10000;
    target = a - b;
    result = Muz_Subtractor(a, b);
    TEST_ASSERT_EQUAL(OK, status_flag);
    TEST_ASSERT_EQUAL(target, result);

    /* Upper end tests */
    a = 0xFFFF;
    b = 0x0800;
    target = a - b;
    result = Muz_Subtractor(a, b);
    TEST_ASSERT_EQUAL(OK, status_flag);
    TEST_ASSERT_EQUAL(target, result);
}

/* Shady Day Tests - What happens if the inputs are not valid?*/
void test_Muz_Subtractor_should_HaveAFailStatusAndReturn0_when_ResultIsNegative(void)
{
    /* Lowest possible values */
    uint16_t a = 10;
    uint16_t b = 100;
    uint16_t target = 0;
    uint16_t result = Muz_Subtractor(a, b);
    TEST_ASSERT_EQUAL(FAIL, status_flag);
    TEST_ASSERT_EQUAL(target, result);
}
