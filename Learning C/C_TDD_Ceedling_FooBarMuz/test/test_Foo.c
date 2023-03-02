#include "unity.h"
#include "Common.h"

#include "Foo.h"
#include "dbg.h"

/**
 * The only thing you as a developer need to do, to create
 * a Mock is to include a file, that (not yet exists: mock_Muz.h).
 * Ceedling reads this and creates a mock module that can be read from
 * mock_<module>.h
 * The Mocks are to be created for interaction based testing of the Foo
 * Module
 */
#include "mock_Muz.h"
#include "mock_Bar.h"

#define VAL 10

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Foo_Init_should_CallMuzSetStatusFunction(void)
{

    /**
     * These are the function calls (with Parameters)
     * which are expected in the FooInit Call
     */
    Muz_SetStatus_Expect(FAIL);

    /* Actually call the Foo Init function */
    Foo_init();
}

void test_Foo_Exec_should_CallBarArrayAdderOnce_AndMuzMultipleTimes(void)
{
    /* Data setup */
    Foo_Data_t foo_test_data = {0};
    uint16_t array[] = {1, 2, 3};
    uint8_t length = 3;
    foo_test_data.array = array;
    foo_test_data.len = length;

    /**
     * Expected function calls (Numbers and order)
     * That will occur once Foo_exec will be called
     * The function will expect to be called with
     * the same arguments as they are introduced in
     * the Foo_exec function
     */

    Bar_ArrayAdder_ExpectAndReturn(foo_test_data.array, foo_test_data.len, OK);
    /**
     * Expected function will be called multiple times
     * (The order of the calls is important. We cannot flip the Bar_ArrayAdder Call
     * with the Muz_Subtractor Call. This will result in a failed test)
     * For the current case, the function does not care about the arguments
     * The provided value is random.
     *
     * The value is executed twice with the data provided above. (This can be
     * seen in Foo.c's exec function), therefore the Dummy_function needs to be
     * called twice.
     */
    // Muz_Subtractor_ExpectAndReturn(0, 0, 10);
    Muz_Subtractor_IgnoreAndReturn(VAL);

    // Muz_Subtractor_ExpectAndReturn(0, 0, 10);

    Foo_exec(&foo_test_data);

    /* Foo_exec has altered the array to be [1, 10, 10] */
    uint16_t desired_out_array[] = {foo_test_data.array[0], VAL, VAL};

    TEST_ASSERT_EQUAL_UINT16_ARRAY(desired_out_array, foo_test_data.array, length);
}