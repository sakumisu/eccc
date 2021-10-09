#ifndef _PID_H
#define _PID_H

#include <stdint.h>

#define PID_CONV_REAL 1.0

typedef struct _pid {
    float SetSpeed;    //�趨ֵ
    float ActualSpeed; //ʵ��ֵ
    float err;         //ƫ��ֵ
    float err_last;    //��һ��ƫ��ֵ
    float err_next;    //��һ��ƫ��ֵ
    float Kp, Ki, Kd;  //�趨ֵ
    float voltage;     //ʵ��ת��ֵ
    float integral;    //�����ۻ�
    float umax;        //ƫ������ֵ
    float umin;        //ƫ������ֵ
} pid_device_t;

void pid_init(pid_device_t *pid);
//��׼PID��ʽ
float pid_located_realize(pid_device_t *pid, float speed);
//����PID������PID��ʽ
float pid_increased_realize(pid_device_t *pid, float speed);
float pid_integral1(pid_device_t *pid, float speed);
//���ַ���
float pid_integral2(pid_device_t *pid, float speed);
//�����PID��ʽ �� Ki*index
float pid_integral3(pid_device_t *pid, float speed);
//�����ֱ��ͣ����������ޣ������ַ��룬�����Ki*index
float pid_integral4(pid_device_t *pid, float speed);

#endif