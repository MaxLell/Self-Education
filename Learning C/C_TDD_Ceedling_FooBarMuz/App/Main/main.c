#include "main.h"
#include "Foo.h"

#ifndef TEST
int main(void)
#else
int main_for_test(void)
#endif
{
    Foo_init();

    Foo_Data_t foo = {0};

    Foo_exec(&foo);
    return 0;
}