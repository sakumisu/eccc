#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>

/* compatible with old version */
#ifndef DBG_TAG
#define DBG_TAG "DEBUG"
#endif

/*
 * The color for terminal (foreground)
 * BLACK    30
 * RED      31
 * GREEN    32
 * YELLOW   33
 * BLUE     34
 * PURPLE   35
 * CYAN     36
 * WHITE    37
 */
#define _DBG_COLOR(n) printf("\033[" #n "m")
#define _DBG_LOG_HDR(lvl_name, color_n) \
    printf("\033[" #color_n "m[" lvl_name "/" DBG_TAG "] ")
#define _DBG_LOG_X_END \
    printf("\033[0m\n")

#define dbg_log_line(lvl, color_n, fmt, ...) \
    do {                                     \
        _DBG_LOG_HDR(lvl, color_n);          \
        printf(fmt, ##__VA_ARGS__);          \
        _DBG_LOG_X_END;                      \
    } while (0)

#define LOG_D(fmt, ...) dbg_log_line("D", 0, fmt, ##__VA_ARGS__)
#define LOG_I(fmt, ...) dbg_log_line("I", 35, fmt, ##__VA_ARGS__)
#define LOG_W(fmt, ...) dbg_log_line("W", 33, fmt, ##__VA_ARGS__)
#define LOG_E(fmt, ...) dbg_log_line("E", 31, fmt, ##__VA_ARGS__)
#define LOG_RAW(...)    printf(__VA_ARGS__)

#endif
