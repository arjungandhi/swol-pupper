#pragma once

class PID
{
private:
    float kp;
    float ki;
    float kd;



public:
    PID(float kp, float ki, float kd);
    ~PID();

    float doPID(float error);

    void updateGains(float *kp = nullptr, float *ki = nullptr, float *kd = nullptr);
};