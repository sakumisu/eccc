#include "auto_init.h"

/*
 * Components Initialization will initialize some driver and components as following
 * order:
 * start         --> 0
 * BOARD_EXPORT      --> 1
 * board_end     --> 1.end
 *
 * DEVICE_EXPORT     --> 2
 * COMPONENT_EXPORT  --> 3
 * FS_EXPORT         --> 4
 * ENV_EXPORT        --> 5
 * APP_EXPORT        --> 6
 *
 * end           --> 6.end
 *
 * These automatically initialization, the driver or component initial function must
 * be defined with:
 * INIT_BOARD_EXPORT(fn);
 * INIT_DEVICE_EXPORT(fn);
 * ...
 * INIT_APP_EXPORT(fn);
 * etc.
 */
static int start(void)
{
    return 0;
}
FUN_INIT_EXPORT(start, "0");

static int board_start(void)
{
    return 0;
}
FUN_INIT_EXPORT(board_start, "0.end");

static int board_end(void)
{
    return 0;
}
FUN_INIT_EXPORT(board_end, "1.end");

static int end(void)
{
    return 0;
}
FUN_INIT_EXPORT(end, "6.end");

/**
 * Components Initialization for board
 */
void board_component_init(void)
{
#if DEBUG
    int result;
    const struct init_desc *desc;
    for (desc = &__init_desc_board_start; desc < &__init_desc_board_end; desc++) {
        printf("initialize %s", desc->fn_name);
        result = desc->fn();
        printf(":%d done\n", result);
    }
#else
    const fn_init_t *fn_ptr;

    for (fn_ptr = &__init_board_start; fn_ptr < &__init_board_end; fn_ptr++) {
        (*fn_ptr)();
    }
    printf("all boards have done\r\n");
#endif
}

/**
 * Components Initialization
 */
void application_component_init(void)
{
#if DEBUG
    int result;
    const struct init_desc *desc;

    rt_kprintf("do components initialization.\n");
    for (desc = &__init_desc_board_end; desc < &__init_desc_end; desc++) {
        printf("initialize %s", desc->fn_name);
        result = desc->fn();
        printf(":%d done\n", result);
    }
#else
    const fn_init_t *fn_ptr;

    for (fn_ptr = &__init_board_end; fn_ptr < &__init_end; fn_ptr++) {
        (*fn_ptr)();
    }
    printf("all applications have done\r\n");
#endif
}