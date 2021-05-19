#pragma once

class PID
{
private:
    double kp;
    double ki;
    double kd;



public:
    PID(double kp, double ki, double kd);
    ~PID();

    double doPID(double error);

    void updateGains(double *kp = nullptr, double *ki = nullptr, double *kd = nullptr);
};