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

/* ���������ʱ���ṹ����� */
static soft_timer_t s_tTmr[TMR_COUNT] = { 0 };

/*
*********************************************************************************************************
*    �� �� ��: bsp_SoftTimerDec
*    ����˵��: ÿ��1ms�����ж�ʱ��������1�����뱻SysTick_ISR�����Ե��á�
*    ��    ��: _tmr : ��ʱ������ָ��
*    �� �� ֵ: ��
*********************************************************************************************************
*/
static void bsp_SoftTimerDec(soft_timer_t *_tmr)
{
    if (_tmr->Count > 0) {
        /* �����ʱ����������1�����ö�ʱ�������־ */
        if (--_tmr->Count == 0) {
            _tmr->Flag = 1;

            /* ������Զ�ģʽ�����Զ���װ������ */
            if (_tmr->Mode == TMR_AUTO_MODE) {
                _tmr->Count = _tmr->PreLoad;
            }
        }
    }
}

/*
*********************************************************************************************************
*    �� �� ��: bsp_StartTimer
*    ����˵��: ����һ����ʱ���������ö�ʱ���ڡ�
*    ��    ��: _id     : ��ʱ��ID��ֵ��0,TMR_COUNT-1�����û���������ά����ʱ��ID���Ա��ⶨʱ��ID��ͻ��
*             _period : ��ʱ���ڣ���λ1ms
*    �� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_StartTimer(uint8_t _id, uint32_t _period, uint8_t mode)
{
    if (_id >= TMR_COUNT) {
        return;
    }

    // DISABLE_INT(); /* ���ж� */

    s_tTmr[_id].Count = _period;   /* ʵʱ��������ֵ */
    s_tTmr[_id].PreLoad = _period; /* �������Զ���װֵ�����Զ�ģʽ������ */
    s_tTmr[_id].Flag = 0;          /* ��ʱʱ�䵽��־ */
    s_tTmr[_id].Mode = mode;       /* 1���Թ���ģʽ */

    // ENABLE_INT(); /* ���ж� */
}

/*
*********************************************************************************************************
*    �� �� ��: bsp_StopTimer
*    ����˵��: ֹͣһ����ʱ��
*    ��    ��:      _id     : ��ʱ��ID��ֵ��0,TMR_COUNT-1�����û���������ά����ʱ��ID���Ա��ⶨʱ��ID��ͻ��
*    �� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_StopTimer(uint8_t _id)
{
    if (_id >= TMR_COUNT) {
        return;
    }

    // DISABLE_INT(); /* ���ж� */

    s_tTmr[_id].Count = 0;            /* ʵʱ��������ֵ */
    s_tTmr[_id].Flag = 0;             /* ��ʱʱ�䵽��־ */
    s_tTmr[_id].Mode = TMR_ONCE_MODE; /* �Զ�����ģʽ */

    //  ENABLE_INT(); /* ���ж� */
}

/*
*********************************************************************************************************
*    �� �� ��: bsp_CheckTimer
*    ����˵��: ��ⶨʱ���Ƿ�ʱ
*    ��    ��: _id     : ��ʱ��ID��ֵ��0,TMR_COUNT-1�����û���������ά����ʱ��ID���Ա��ⶨʱ��ID��ͻ��
*              _period : ��ʱ���ڣ���λ1ms
*    �� �� ֵ: ���� 0 ��ʾ��ʱδ���� 1��ʾ��ʱ��
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
    /* ÿ��1ms���������ʱ���ļ��������м�һ���� */
    for (uint8_t i = 0; i < TMR_COUNT; i++) {
        bsp_SoftTimerDec(&s_tTmr[i]);
    }
}
