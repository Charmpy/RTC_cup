from pyPS4Controller.controller import Controller
import serial
from time import sleep


class MyController(Controller):
    def __init__(self, **kwargs):
        super().__init__(self, **kwargs)
        self.L1_on = False
        self.R1_on = False
        self.ser = serial.Serial("/dev/serial0", 115200)

        self.default_pos = {'A1': 0, 'A2': 0, 'A3': 0, 'A4': 0}
        self.current_pos = {'A1': 0, 'A2': 0, 'A3': 0, 'A4': 0}
        self.restrictions = {'A1': (-4096, 4096), 'A2': (-4096, 4096), 'A3': (-4096, 4096), 'A4': (-4096, 4096)}

    ##############################################
    #                   Макросы                  #
    ##############################################

    def on_L1_press(self):
        self.L1_on = True

    def on_L1_release(self):
        self.L1_on = False

    def on_R1_press(self):
        self.R1_on = True

    def on_R1_release(self):
        self.R1_on = False

    ##############################################
    #             маршевые двигатели             #
    ##############################################

    def _motor_command_generator(self, index, value, reverse=False, stp=False):
        if reverse:
            return ("M" + str(index) + str(round(1000 + (value + 34000) / (34000 * 2) * 1000)).rjust(4, '0')).encode()
        else:
            return ("M" + str(index) + str(round((value + 34000) / (34000 * 2) * 1000)).rjust(4, '0')).encode()

        if stp:
            return ("M" + str(index) + str(0).rjust(4, '0')).encode()

    def on_R2_press(self, value):
        self.ser.write(self._motor_command_generator(1, value, self.R1_on))
        self.ser.write(self._motor_command_generator(3, value, self.R1_on))
        # self.ser.write(b'M01000')

    def on_L2_press(self, value):
        self.ser.write(self._motor_command_generator(2, value, self.L1_on))
        self.ser.write(self._motor_command_generator(4, value, self.L1_on))

    def on_R2_release(self):
        self.ser.write(self._motor_command_generator(1, 0, stp=True))
        self.ser.write(self._motor_command_generator(3, 0, stp=True))
        # self.ser.write(b'M01000')

    def on_L2_release(self):
        self.ser.write(self._motor_command_generator(2, 0, stp=True))
        self.ser.write(self._motor_command_generator(4, 0, stp=True))

    ##############################################
    #                Сервоприводы                #
    ##############################################

    def send(self, lit, sign, val=100):
        if lit[0] != 'A' or self.restrictions[lit][0] < self.current_pos[lit] + sign * val < self.restrictions[lit][1]:
            self.ser.write((lit + str(sign * val).rjust(4, '0')).encode())
            if lit[0] == 'A':
                self.current_pos[lit] += sign * val

    def on_x_press(self):
        self.send('A2', 1)

    def on_triangle_press(self):
        self.send('A2', -1)

    def on_circle_press(self):
        self.send('A4', 1)

    def on_square_press(self):
        self.send('A4', -1)

    def on_up_arrow_press(self):
        self.send('A1', -1)

    def on_down_arrow_press(self):
        self.send('A1', 1)

    def on_left_arrow_press(self):
        self.send('A3', -1)

    def on_right_arrow_press(self):
        self.send('A3', 1)


controller = MyController(interface="/dev/input/js0", connecting_using_ds4drv=False)
controller.listen(timeout=100)