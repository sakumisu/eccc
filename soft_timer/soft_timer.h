/*
 * Copyright (c) 2016 Zibin Zheng <znbin@qq.com>
 * All rights reserved
 */

#ifndef _SOFT_TIMER_H_
#define _SOFT_TIMER_H_

#include "stdint.h"

typedef struct Timer {
    uint32_t timeout;
    uint32_t repeat;
    void (*timeout_cb)(void);
    struct Timer *next;
} Timer;

#ifdef __cplusplus
extern "C" {
#endif

void timer_init(struct Timer *handle, void (*timeout_cb)(), uint32_t timeout, uint32_t repeat);
int timer_start(struct Timer *handle);
void timer_stop(struct Timer *handle);
void timer_ticks(void);
void timer_loop(void);

/*
    在此定义若干个软件定时器全局变量
    注意，必须增加__IO 即 volatile，因为这个变量在中断和主程序中同时被访问，有可能造成编译器错误优化。
*/
#define TMR_COUNT 4 /* 软件定时器的个数 （定时器ID范围 0 - 3) */

/* 定时器结构体，成员变量必须是 volatile, 否则C编译器优化时可能有问题 */
typedef enum {
    TMR_ONCE_MODE = 0, /* 一次工作模式 */
    TMR_AUTO_MODE = 1  /* 自动定时工作模式 */
} TMR_MODE_E;

/* 定时器结构体，成员变量必须是 volatile, 否则C编译器优化时可能有问题 */
typedef struct
{
    volatile uint8_t Mode;     /* 计数器模式，1次性 */
    volatile uint8_t Flag;     /* 定时到达标志  */
    volatile uint32_t Count;   /* 计数器 */
    volatile uint32_t PreLoad; /* 计数器预装值 */
} soft_timer_t;
#ifdef __cplusplus
}
#endif

#endif
