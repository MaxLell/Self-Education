

#include "unity.h"

#include "main.h"
#include "mock_Foo.h"

void setUp(void)
{
}

void tearDown(void)
{
}

extern int main_for_test();
void test_main_should_CallFooInitAndFooExec(void)
{

    Foo_init_Expect();
    Foo_Data_t foo = {0};

    Foo_exec_ExpectAndReturn(&foo, 1);

    main_for_test();
}
