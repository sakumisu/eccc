#include "pid.h"
#include <math.h>

void pid_init(pid_device_t *pid)
{
    pid->SetSpeed = 0.0;
    pid->ActualSpeed = 0.0;
    pid->err = 0.0;
    pid->err_last = 0.0;
    pid->err_next = 0.0;
    pid->voltage = 0.0;
    pid->integral = 0.0;
    pid->Kp = 0.2;
    //pid->Ki = 0.015;
    //pid->Ki = 0.04;
    //pid->Ki = 0.1;
    pid->Ki = 0.2;
    pid->Kd = 0.2;
    pid->umax = 400;
    pid->umin = -200;
}
//位置PID公式
float pid_located_realize(pid_device_t *pid, float speed)
{
    pid->SetSpeed = speed;
    pid->err = pid->SetSpeed - pid->ActualSpeed;
    pid->integral += pid->err;
    pid->voltage = pid->Kp * pid->err + pid->Ki * pid->integral + pid->Kd * (pid->err - pid->err_last);
    pid->err_last = pid->err;
    pid->ActualSpeed = pid->voltage * PID_CONV_REAL;
    return pid->ActualSpeed;
}
//利用PID增量的PID公式
float pid_increased_realize(pid_device_t *pid, float speed)
{
    pid->SetSpeed = speed;
    pid->err = pid->SetSpeed - pid->ActualSpeed;
    float increment = pid->Kp * (pid->err - pid->err_next) + pid->Ki * pid->err + pid->Kd * (pid->err - 2 * pid->err_next + pid->err_last);
    pid->ActualSpeed += increment;
    pid->err_last = pid->err_next;
    pid->err_next = pid->err;
    return pid->ActualSpeed;
}

float pid_integral1(pid_device_t *pid, float speed)
{
    float index;
    pid->SetSpeed = speed;
    pid->err = pid->SetSpeed - pid->ActualSpeed;
    if (fabs(pid->err) > 200) {
        index = 0;
    } else {
        index = 1.0;
        pid->integral += pid->err;
    }
    pid->voltage = pid->Kp * pid->err + index * pid->Ki * pid->integral + pid->Kd * (pid->err - pid->err_last);
    pid->err_last = pid->err;
    pid->ActualSpeed = pid->voltage * PID_CONV_REAL;
    return pid->ActualSpeed;
}
//积分分离
float pid_integral2(pid_device_t *pid, float speed)
{
    float index;
    pid->SetSpeed = speed;
    pid->err = pid->SetSpeed - pid->ActualSpeed;
    if (pid->ActualSpeed > pid->umax) {
        if (fabsf(pid->err) > 200) {
            index = 0;
        } else {
            index = 1.0;
            if (pid->err < 0)
                pid->integral += pid->err;
        }
    } else if (pid->ActualSpeed < pid->umin) {
        if (fabsf(pid->err) > 200) {
            index = 0;
        } else {
            index = 1.0;
            if (pid->err > 0)
                pid->integral += pid->err;
        }
    } else {
        if (fabsf(pid->err) > 200) {
            index = 0;
        } else {
            index = 1.0;
            pid->integral += pid->err;
        }
    }

    pid->voltage = pid->Kp * pid->err + index * pid->Ki * pid->integral + pid->Kd * (pid->err - pid->err_last);
    pid->err_last = pid->err;
    pid->ActualSpeed = pid->voltage * PID_CONV_REAL;
    return pid->ActualSpeed;
}
//变积分PID公式 ： Ki*index
float pid_integral3(pid_device_t *pid, float speed)
{
    float index;
    pid->SetSpeed = speed;
    pid->err = pid->SetSpeed - pid->ActualSpeed;
    if (fabsf(pid->err) > 200) {
        index = 0;
    } else {
        if (fabsf(pid->err) < 180)
            index = 1.0;
        else
            index = (200 - fabsf(pid->err)) / 20;
        pid->integral += pid->err;
    }
    pid->voltage = pid->Kp * pid->err + index * pid->Ki * pid->integral + pid->Kd * (pid->err - pid->err_last);
    pid->err_last = pid->err;
    pid->ActualSpeed = pid->voltage * PID_CONV_REAL;
    return pid->ActualSpeed;
}
//抗积分饱和（设置上下限），积分分离，变积分Ki*index
float pid_integral4(pid_device_t *pid, float speed)
{
    float index;
    pid->SetSpeed = speed;
    pid->err = pid->SetSpeed - pid->ActualSpeed;
    if (pid->ActualSpeed > pid->umax) {
        if (fabsf(pid->err) > 200) {
            index = 0;
        } else {
            if (fabsf(pid->err) < 180)
                index = 1.0;
            else
                index = (200 - fabsf(pid->err)) / 20;
            if (pid->err < 0)
                pid->integral += pid->err;
        }
    } else if (pid->ActualSpeed < pid->umin) {
        if (fabsf(pid->err) > 200) {
            index = 0;
        } else {
            if (fabsf(pid->err) < 180)
                index = 1.0;
            else
                index = (200 - fabsf(pid->err)) / 20;
            if (pid->err > 0)
                pid->integral += pid->err;
        }
    } else {
        if (fabsf(pid->err) > 200) {
            index = 0;
        } else {
            if (fabsf(pid->err) < 180)
                index = 1.0;
            else
                index = (200 - fabsf(pid->err)) / 20;
            pid->integral += pid->err;
        }
    }

    pid->voltage = pid->Kp * pid->err + index * pid->Ki * pid->integral + pid->Kd * (pid->err - pid->err_last);
    pid->err_last = pid->err;
    pid->ActualSpeed = pid->voltage * PID_CONV_REAL;
    return pid->ActualSpeed;
}