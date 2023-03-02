#include "Bar.h"

STATIC uint8_t Bar_IsSumOutOfBounds(uint16_t *inout_array, uint16_t len)
{
    uint32_t input_threshold = 0x0000FFFF;
    uint32_t guard = 0;
    uint8_t IsOutOfBounds = TRUE;

    for (uint8_t i = 0; i < len; i++)
    {
        guard += inout_array[i];
        if (guard > input_threshold)
        {
            IsOutOfBounds = TRUE;
            break;
        }
        else
        {
            IsOutOfBounds = FALSE;
        }
    }
    return IsOutOfBounds;
}

uint8_t Bar_ArrayAdder(uint16_t *inout_array, uint16_t len)
{
    uint8_t status = FAIL;

    if (len == 0)
    {
        return FAIL;
    }
    else
    {
        if (Bar_IsSumOutOfBounds(inout_array, len) == TRUE)
        {
            status = FAIL;
        }
        else
        {
            status = OK;
        }
    }
    if (status == OK)
    {
        uint16_t tmp = inout_array[0];
        inout_array[0] = 0;
        for (uint8_t i = 0; i < len; i++)
        {

            if (i == 0)
            {
                inout_array[0] += tmp;
            }
            else
            {
                inout_array[0] += inout_array[i];
            }
        }
        status = OK;
    }
    return status;
}
