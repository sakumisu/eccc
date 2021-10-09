/* BSD strsep function */

/* Copyright 2002, Red Hat Inc. */

/* undef STRICT_ANSI so that strsep prototype will be defined */
#include <string.h>

extern char *__strtok_r(char *, const char *, char **, int);

char *
strsep(char **source_ptr,
       const char *delim)
{
    return __strtok_r(*source_ptr, delim, source_ptr, 0);
}
