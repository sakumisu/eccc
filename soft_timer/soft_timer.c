/*
 * Copyright (c) 2016 Zibin Zheng <znbin@qq.com>
 * All rights reserved
 */

#include "soft_timer.h"

//timer handle list head.
static struct Timer *head_handle = 0;

//Timer ticks
static uint32_t _timer_ticks = 0;

/**
  * @brief  Initializes the timer struct handle.
  * @param  handle: the timer handle strcut.
  * @param  timeout_cb: timeout callback.
  * @param  repeat: repeat interval time.
  * @retval None
  */
void timer_init(struct Timer *handle, void (*timeout_cb)(), uint32_t timeout, uint32_t repeat)
{
    // memset(handle, sizeof(struct Timer), 0);
    handle->timeout_cb = timeout_cb;
    handle->timeout = _timer_ticks + timeout;
    handle->repeat = repeat;
}

/**
  * @brief  Start the timer work, add the handle into work list.
  * @param  btn: target handle strcut.
  * @retval 0: succeed. -1: already exist.
  */
int timer_start(struct Timer *handle)
{
    struct Timer *target = head_handle;
    while (target) {
        if (target == handle)
            return -1; //already exist.
        target = target->next;
    }
    handle->next = head_handle;
    head_handle = handle;
    return 0;
}

/**
  * @brief  Stop the timer work, remove the handle off work list.
  * @param  handle: target handle strcut.
  * @retval None
  */
void timer_stop(struct Timer *handle)
{
    struct Timer **curr;
    for (curr = &head_handle; *curr;) {
        struct Timer *entry = *curr;
        if (entry == handle) {
            *curr = entry->next;
            //			free(entry);
        } else
            curr = &entry->next;
    }
}

/**
  * @brief  main loop.
  * @param  None.
  * @retval None
  */
void timer_loop()
{
    struct Timer *target;
    for (target = head_handle; target; target = target->next) {
        if (_timer_ticks >= target->timeout) {
            if (target->repeat == 0) {
                timer_stop(target);
            } else {
                target->timeout = _timer_ticks + target->repeat;
            }
            target->timeout_cb();
        }
    }
}

/**
  * @brief  background ticks, timer repeat invoking interval 1ms.
  * @param  None.
  * @retval None.
  */
void timer_ticks()
{
    _timer_ticks++;
}

/* 定于软件定时器结构体变量 */
static soft_timer_t s_tTmr[TMR_COUNT] = { 0 };

/*
*********************************************************************************************************
*    函 数 名: bsp_SoftTimerDec
*    功能说明: 每隔1ms对所有定时器变量减1。必须被SysTick_ISR周期性调用。
*    形    参: _tmr : 定时器变量指针
*    返 回 值: 无
*********************************************************************************************************
*/
static void bsp_SoftTimerDec(soft_timer_t *_tmr)
{
    if (_tmr->Count > 0) {
        /* 如果定时器变量减到1则设置定时器到达标志 */
        if (--_tmr->Count == 0) {
            _tmr->Flag = 1;

            /* 如果是自动模式，则自动重装计数器 */
            if (_tmr->Mode == TMR_AUTO_MODE) {
                _tmr->Count = _tmr->PreLoad;
            }
        }
    }
}

/*
*********************************************************************************************************
*    函 数 名: bsp_StartTimer
*    功能说明: 启动一个定时器，并设置定时周期。
*    形    参: _id     : 定时器ID，值域【0,TMR_COUNT-1】。用户必须自行维护定时器ID，以避免定时器ID冲突。
*             _period : 定时周期，单位1ms
*    返 回 值: 无
*********************************************************************************************************
*/
void bsp_StartTimer(uint8_t _id, uint32_t _period, uint8_t mode)
{
    if (_id >= TMR_COUNT) {
        return;
    }

    // DISABLE_INT(); /* 关中断 */

    s_tTmr[_id].Count = _period;   /* 实时计数器初值 */
    s_tTmr[_id].PreLoad = _period; /* 计数器自动重装值，仅自动模式起作用 */
    s_tTmr[_id].Flag = 0;          /* 定时时间到标志 */
    s_tTmr[_id].Mode = mode;       /* 1次性工作模式 */

    // ENABLE_INT(); /* 开中断 */
}

/*
*********************************************************************************************************
*    函 数 名: bsp_StopTimer
*    功能说明: 停止一个定时器
*    形    参:      _id     : 定时器ID，值域【0,TMR_COUNT-1】。用户必须自行维护定时器ID，以避免定时器ID冲突。
*    返 回 值: 无
*********************************************************************************************************
*/
void bsp_StopTimer(uint8_t _id)
{
    if (_id >= TMR_COUNT) {
        return;
    }

    // DISABLE_INT(); /* 关中断 */

    s_tTmr[_id].Count = 0;            /* 实时计数器初值 */
    s_tTmr[_id].Flag = 0;             /* 定时时间到标志 */
    s_tTmr[_id].Mode = TMR_ONCE_MODE; /* 自动工作模式 */

    //  ENABLE_INT(); /* 开中断 */
}

/*
*********************************************************************************************************
*    函 数 名: bsp_CheckTimer
*    功能说明: 检测定时器是否超时
*    形    参: _id     : 定时器ID，值域【0,TMR_COUNT-1】。用户必须自行维护定时器ID，以避免定时器ID冲突。
*              _period : 定时周期，单位1ms
*    返 回 值: 返回 0 表示定时未到， 1表示定时到
*********************************************************************************************************
*/
uint8_t bsp_CheckTimer(uint8_t _id)
{
    if (_id >= TMR_COUNT) {
        return 0;
    }

    if (s_tTmr[_id].Flag == 1) {
        s_tTmr[_id].Flag = 0;
        return 1;
    } else {
        return 0;
    }
}

void SysTick_ISR(void)
{
    /* 每隔1ms，对软件定时器的计数器进行减一操作 */
    for (uint8_t i = 0; i < TMR_COUNT; i++) {
        bsp_SoftTimerDec(&s_tTmr[i]);
    }
}
