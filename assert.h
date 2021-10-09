#ifndef _ASSERT__H
#define _ASSERT__H

#define ASSERT_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)

#define ASSERT_LOC(test)                            \
    ASSERT_PRINT("ASSERTION FAIL [%s] @ %s:%d\r\n", \
                 STRINGIFY(test),                   \
                 __FILE__, __LINE__)

#define ASSERT_NO_MSG(test)   \
    do {                      \
        if (!(test)) {        \
            ASSERT_LOC(test); \
        }                     \
    } while (false)

#define ASSERT(test, fmt, ...)                \
    do {                                      \
        if (!(test)) {                        \
            ASSERT_LOC(test);                 \
            ASSERT_PRINT(fmt, ##__VA_ARGS__); \
        }                                     \
    } while (false)

#define ASSERT_EVAL(expr1, expr2, test, fmt, ...) \
    do {                                          \
        expr2;                                    \
        ASSERT(test, fmt, ##__VA_ARGS__);         \
    } while (false)

#ifdef assert
#undef assert
#endif
#define assert(EX)                                                                                                   \
    if (!(#EX)) {                                                                                                    \
        printf("(%s) assertion failed at file %s, function:%s, line %d\r\n", #EX, __FILE__, __FUNCTION__, __LINE__); \
        while (1)                                                                                                    \
            ;                                                                                                        \
    }

#endif
