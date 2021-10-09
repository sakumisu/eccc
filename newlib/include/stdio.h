/* stdio.h */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_LIB_LIBC_MINIMAL_INCLUDE_STDIO_H_
#define ZEPHYR_LIB_LIBC_MINIMAL_INCLUDE_STDIO_H_

#include <stdarg.h> /* Needed to get definition of va_list */
#include <bits/restrict.h>
#include <stddef.h>

typedef int (*cbprintf_cb)(/* int c, void *ctx */);

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__FILE_defined)
#define __FILE_defined
typedef int FILE;
#endif

#if !defined(EOF)
#define EOF (-1)
#endif

#define stdin  ((FILE *)1)
#define stdout ((FILE *)2)
#define stderr ((FILE *)3)

extern int sprintf(char *, const char *, ...);
extern int vsprintf(char *, const char *, va_list);
extern int snprintf(char *__restrict, size_t, const char *__restrict, ...);
extern int vsnprintf(char *, size_t, const char *, va_list);
extern int sscanf(const char *, const char *, ...);
extern int vsscanf(const char *, const char *, va_list);

int cbvprintf(cbprintf_cb out, void *ctx, const char *format, va_list ap);

int printf(const char *_MLIBC_RESTRICT fmt, ...);

int fprintf(FILE *_MLIBC_RESTRICT stream,
            const char *_MLIBC_RESTRICT format, ...);

int vprintf(const char *_MLIBC_RESTRICT fmt, va_list list);

int vfprintf(FILE *_MLIBC_RESTRICT stream,
             const char *_MLIBC_RESTRICT format,
             va_list ap);

int puts(const char *s);

int fputc(int c, FILE *stream);
int fputs(const char *_MLIBC_RESTRICT s, FILE *_MLIBC_RESTRICT stream);
size_t fwrite(const void *_MLIBC_RESTRICT ptr, size_t size, size_t nitems,
              FILE *_MLIBC_RESTRICT stream);
static inline int putc(int c, FILE *stream)
{
    return fputc(c, stream);
}
static inline int putchar(int c)
{
    return putc(c, stdout);
}

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_LIB_LIBC_MINIMAL_INCLUDE_STDIO_H_ */
