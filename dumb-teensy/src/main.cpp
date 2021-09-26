#include "Arduino.h"
#include "C610Bus.h"
// #include "Motor.h"


long last_command = 0;
C610Bus<CAN1> front_bus;
C610Bus<CAN2> back_bus;

// Motor<CAN1> m0(&front_bus, 0);
// Motor<CAN1> m1(&front_bus, 1);
// Motor<CAN1> m2(&front_bus, 2);
// Motor<CAN1> m3(&front_bus, 3);
// Motor<CAN1> m4(&front_bus, 4);
// Motor<CAN1> m5(&front_bus, 5);

// Motor<CAN2> m6(&back_bus, 0);
// Motor<CAN2> m7(&back_bus, 1);
// Motor<CAN2> m8(&back_bus, 2);
// Motor<CAN2> m9(&back_bus, 3);
// Motor<CAN2> m10(&back_bus, 4);
// Motor<CAN2> m11(&back_bus, 5);


void setup(){
    Serial.begin(9600);
}

void loop()
{
    front_bus.PollCAN(); // Check for messages from the motors
    back_bus.PollCAN();

    long now = millis();
    if (now - last_command >= 10) // Loop at 100Hz. You should limit the rate at which you call CommandTorques to <1kHz to avoid saturating the CAN bus bandwidth
    {
        float current_pos = front_bus.Get(4).Position();
        
        // float error = target_pos - current_pos;

        // float command_torque = error * kp;

        // front_bus.CommandTorques(command_torque, 0, 0, 0 , C610Subbus::kIDZeroToThree);      // Command 100mA to motor 1, 200ma to motor 2, etc. The last parameter specifies to command the motors with IDs 1-4

        Serial.println(current_pos);

        last_command = now;
    }
}