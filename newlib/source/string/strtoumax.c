/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define TYPE uintmax_t
#define NAME strtoumax

TYPE NAME(const char *nptr, char **endptr, int base)
{
    return (TYPE)strntoumax(nptr, endptr, base, ~(size_t)0);
}