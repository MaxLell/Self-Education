#include "Muz.h"

STATIC uint8_t status_flag;

void Muz_SetStatus(uint8_t status)
{
    status = status_flag;
}

uint16_t Muz_Subtractor(uint16_t a, uint16_t b)
{
    uint16_t result;
    if (b > a)
    {
        /*Then the result will be negative and therefore invalid*/
        result = 0;
        status_flag = FAIL;
    }
    else
    {
        result = (a - b);
        status_flag = OK;
    }

    return result;
}