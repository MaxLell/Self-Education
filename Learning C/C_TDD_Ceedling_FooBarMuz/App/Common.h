#include <stdint.h>
#include <stdio.h>

#define OK 1
#define FAIL 0

#define TRUE 1
#define FALSE 0

#ifdef TEST
#define STATIC
#else
#define STATIC static
#endif