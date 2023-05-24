from pyPS4Controller.controller import Controller
import serial
from time import sleep

class MyController(Controller):
    def __init__(self, **kwargs):
        super().__init__(self, **kwargs)
        self.L1_on = False
        self.R1_on = False
        self.ser = serial.Serial("/dev/ttyACM0", 57600)


        self.default_pos = {'A1': 0, 'A2': 0, 'A3': 0, 'A4': 0}
        self.current_pos = {'A1': 0, 'A2': 0, 'A3': 0, 'A4': 0}
        self.restrictions = {'A1': (-4096, 4096), 'A2': (-4096, 4096), 'A3': (-4096, 4096), 'A4': (-4096, 4096)}

    def send(self, lit, sign, val = 100):
        if lit[0] != 'A' or self.restrictions[lit][0] < self.current_pos[lit] + sign * val < self.restrictions[lit][1] :
            self.ser.write((lit + str(sign * val).rjust(4, '0')).encode())
            if lit[0] == 'A':
                self.current_pos[lit] += sign * val

    def on_L1_press(self):
        self.L1_on = True

    def on_L1_release(self):
        self.L1_on = False

    def on_R1_press(self):
        self.R1_on = True

    def on_R1_release(self):
        self.R1_on = False

    def on_L2_press(self, value):
        if self.L1_on: sign = -1
        else: sign = 1

        # нужно вычислить коэффициент k
        k = 1
        self.send("M1", sign, value * k)
        self.send("M3", sign, value * k)

    def on_L2_release(self):
        self.send("M1", 1, 0)
        self.send("M3", 1, 0)

    def on_R2_press(self, value):
        if self.L1_on: sign = -1
        else: sign = 1


        # нужно вычислить коэффициент k
        k = 1
        self.send("M2", sign, value * k)
        self.send("M4", sign, value * k)

    def on_R2_release(self):
        self.send("M2", 1, 0)
        self.send("M4", 1, 0)

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



#     def on_L3_y_at_rest(self):
#         pass
#
#     # self.ser.write(('A' + str(2048)).encode())
#     def on_R3_y_at_rest(self):
#         # self.ser.write(('B' + str(2048)).encode())
#         pass
#
#     def on_L3_down(self, value):
#         print(str(2048 - int(value / 16)).rjust(4, '0'))
#         # self.ser.write(('A' + str(2048 - int(value/16)).rjust(4, '0')).encode())
#
#     def on_L3_up(self, value):
#         print(str(2048 - int(value / 16)).rjust(4, '0'))
#         # self.ser.write(('A' + str(2048 - int(value/16)).rjust(4, '0')).encode())
#
#     def on_R3_up(self, value):
#         print(str(2048 - int(value / 16)).rjust(4, '0'))
#         # self.ser.write(('B' + str(2048 - int(value / 16)).rjust(4, '0')).encode())
#
#     def on_R3_down(self, value):
#         print(str(2048 - int(value / 16)).rjust(4, '0'))
#         # self.ser.write(('B' + str(2048 - int(value / 16)).rjust(4, '0')).encode())

controller = MyController(interface="/dev/input/js0", connecting_using_ds4drv=False)
controller.listen()

    ## https://github.com/ArturSpirin/pyPS4Controller