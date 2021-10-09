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
    �ڴ˶������ɸ������ʱ��ȫ�ֱ���
    ע�⣬��������__IO �� volatile����Ϊ����������жϺ���������ͬʱ�����ʣ��п�����ɱ����������Ż���
*/
#define TMR_COUNT 4 /* �����ʱ���ĸ��� ����ʱ��ID��Χ 0 - 3) */

/* ��ʱ���ṹ�壬��Ա���������� volatile, ����C�������Ż�ʱ���������� */
typedef enum {
    TMR_ONCE_MODE = 0, /* һ�ι���ģʽ */
    TMR_AUTO_MODE = 1  /* �Զ���ʱ����ģʽ */
} TMR_MODE_E;

/* ��ʱ���ṹ�壬��Ա���������� volatile, ����C�������Ż�ʱ���������� */
typedef struct
{
    volatile uint8_t Mode;     /* ������ģʽ��1���� */
    volatile uint8_t Flag;     /* ��ʱ�����־  */
    volatile uint32_t Count;   /* ������ */
    volatile uint32_t PreLoad; /* ������Ԥװֵ */
} soft_timer_t;
#ifdef __cplusplus
}
#endif

#endif
