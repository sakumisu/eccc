#ifndef _PID_H
#define _PID_H

#include <stdint.h>

#define PID_CONV_REAL 1.0

typedef struct _pid {
    float SetSpeed;    //设定值
    float ActualSpeed; //实际值
    float err;         //偏差值
    float err_last;    //上一次偏差值
    float err_next;    //下一次偏差值
    float Kp, Ki, Kd;  //设定值
    float voltage;     //实际转换值
    float integral;    //积分累积
    float umax;        //偏差上限值
    float umin;        //偏差下限值
} pid_device_t;

void pid_init(pid_device_t *pid);
//标准PID公式
float pid_located_realize(pid_device_t *pid, float speed);
//利用PID增量的PID公式
float pid_increased_realize(pid_device_t *pid, float speed);
float pid_integral1(pid_device_t *pid, float speed);
//积分分离
float pid_integral2(pid_device_t *pid, float speed);
//变积分PID公式 ： Ki*index
float pid_integral3(pid_device_t *pid, float speed);
//抗积分饱和（设置上下限），积分分离，变积分Ki*index
float pid_integral4(pid_device_t *pid, float speed);

#endif