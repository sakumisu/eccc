/* string.h */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_LIB_LIBC_MINIMAL_INCLUDE_STRING_H_
#define ZEPHYR_LIB_LIBC_MINIMAL_INCLUDE_STRING_H_

#include <stddef.h>
#include <stdint.h>
#include <bits/restrict.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

extern int bcmp(const void *, const void *, size_t); /* LEGACY */
extern void bcopy(const void *, void *, size_t);     /* LEGACY */
extern void bzero(void *, size_t);                   /* LEGACY */

char *index(const char *, int);  /* LEGACY */
char *rindex(const char *, int); /* LEGACY */

extern void *memccpy(void *, const void *, int, size_t);
extern void *memchr(const void *, int, size_t);
extern int memcmp(const void *, const void *, size_t);
extern void *memcpy(void *, const void *, size_t);
extern void *memmem(const void *, size_t, const void *, size_t);
extern void *memmove(void *, const void *, size_t);
extern void *mempcpy(void *, const void *, size_t);
extern void *memrchr(const void *, int, size_t);
extern void *memset(void *, int, size_t);
extern void memswap(void *, void *, size_t);

extern int strcasecmp(const char *, const char *);
extern char *strcasestr(const char *, const char *);
extern char *strcat(char *, const char *);
extern char *strchr(const char *, int);
extern char *strchrnul(const char *, int);
extern int strcmp(const char *, const char *);
extern int strcoll(const char *, const char *);
extern char *strcpy(char *, const char *);
extern size_t strcspn(const char *, const char *);
extern size_t strlcat(char *, const char *, size_t);
extern size_t strlcpy(char *, const char *, size_t);
extern size_t strlen(const char *);
extern char *strlwr(char *);
extern int strncasecmp(const char *, const char *, size_t);
extern char *strncat(char *, const char *, size_t);
extern int strncmp(const char *, const char *, size_t);
extern char *strncpy(char *, const char *, size_t);
extern char *strndup(const char *str, size_t n);
extern size_t strnlen(const char *, size_t);
extern char *strnstr(const char *, const char *, size_t);
extern char *strpbrk(const char *, const char *);
extern char *strrchr(const char *, int);
extern char *strsep(char **, const char *);
extern size_t strspn(const char *, const char *);
extern char *strstr(const char *, const char *);
extern char *strdup(const char *str);
extern char *strtok(char *, const char *);
extern char *strtok_r(char *, const char *, char **);
extern size_t __strxspn(const char *s, const char *map, int parity);

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_LIB_LIBC_MINIMAL_INCLUDE_STRING_H_ */
