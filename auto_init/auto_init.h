#ifndef _AUTO_INIT_H
#define _AUTO_INIT_H

#include "system.h"

/* initialization export */
typedef int (*fn_init_t)(void);
#if DEBUG
struct init_desc {
    const char *fn_name;
    const fn_init_t fn;
};
#define INIT_EXPORT(fn, level)        \
    const char __##fn##_name[] = #fn; \
    __USED__ const struct init_desc __init_desc_##fn SECTION(".fn." level) = { __##fn##_name, fn };
#else
#define FUN_INIT_EXPORT(fn, level) \
    __USED__ const fn_init_t __init_##fn SECTION(".fn." level) = fn
#endif

/* board init routines will be called in board_init() function */
#define BOARD_INIT_EXPORT(fn) FUN_INIT_EXPORT(fn, "1")

/* pre/device/component/env/app init routines will be called in init_thread */
/* components pre-initialization (pure software initilization) */
#define PREV_INIT_EXPORT(fn) FUN_INIT_EXPORT(fn, "2")
/* device initialization */
#define DEVICE_INIT_EXPORT(fn) FUN_INIT_EXPORT(fn, "3")
/* components initialization (dfs, lwip, ...) */
#define COMPONENT_INIT_EXPORT(fn) FUN_INIT_EXPORT(fn, "4")
/* environment initialization (mount disk, ...) */
#define ENV_INIT_EXPORT(fn) FUN_INIT_EXPORT(fn, "5")
/* appliation initialization (rtgui application etc ...) */
#define APP_INIT_EXPORT(fn) FUN_INIT_EXPORT(fn, "6")

void board_component_init(void);
void application_component_init(void);
#endif