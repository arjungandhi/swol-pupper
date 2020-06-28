import serial
import msgpack
import numpy as np

class HardwareInterface:
    def __init__(self, port, baudrate=500000):
        self.serial_handle = serial.Serial(
            port=port,
            baudrate=baudrate,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            timeout=0,
        )
        self.set_default_gains()

    def set_default_gains(self):
        kp = 20.0
        kd = 0.008
        max_current = 6.0
        self.send_dict({"kp":kp, "kd":kd, "max_current":max_current})

    def send_dict(self, dict):
        out = msgpack.packb(dict)
        self.serial_handle.write(b'<' + out + b'>')

    def set_actuator_postions(self, joint_angles):
        """[summary]

        Parameters
        ----------
        joint_angles : [numpy array (3, 4)]
            Joint angles, radians, with body axes RH rule convention
        """
        direction_multiplier = np.array(
            [[1, 1, -1, -1], 
            [-1, 1, -1, 1], 
            [1, -1, 1, -1]]
        )
        motor_frame_angles = joint_angles * direction_multiplier
        joint_angles_vector = list(motor_frame_angles.flatten('F'))
        self.send_dict({"pos":joint_angles_vector})

    