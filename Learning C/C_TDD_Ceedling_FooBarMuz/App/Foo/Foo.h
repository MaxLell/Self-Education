#ifndef FOO_H
#define FOO_H

#include "Common.h"

typedef struct _Foo_Data_t
{
    uint16_t *array;
    uint8_t len;
} Foo_Data_t;

void Foo_init(void);

uint8_t Foo_exec(Foo_Data_t *foo_data);

#endif // FOO_H
