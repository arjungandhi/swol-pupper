#pragma once
#include "PID.h"
#include "C610Bus.h"


enum ControlState {position, velocity, torque, idle};

template <CAN_DEV_TABLE T> class Motor {

    private: 
        C610Bus<T>* bus;

        ControlState controlState;
        
        float setpoint;
        float position; 
        float velocity; 
        float torque;

        PID positionController;
        PID velocityController;
        PID torqueController; 

    public:

        Motor(C610Bus<T>* bus, int pos);

        ~Motor();

        void setSetpoint(float setpoint);

        float getTarget();

        void setState(ControlState state);
};