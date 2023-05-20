'''
  A     B
  |     |
  |     |
  E-----F
     |
     |
  H-----G
  |     |
  |     |
  D     C
'''

from pyPS4Controller.controller import Controller
import serial
from time import sleep

class MyController(Controller):
    def __init__(self, **kwargs):
        super().__init__(self, **kwargs)
        self.L1_on = False
        self.R1_on = False
        self.L2_on = False
        self.R2_on = False
        self.ser = serial.Serial("/dev/ttyACM0", 57600)

        self.names_def = {'A': 'A', 'B': 'B', 'C': 'C', 'D': 'D', 'E': 'E', 'F': 'F', 'G': 'G', 'H': 'H'}
        self.default_pos = {'A': 0, 'B': 0, 'C': 0, 'D': 0, 'E': 0, 'F': 0, 'G': 0, 'H': 0}
        self.current_pos = {'A': 0, 'B': 0, 'C': 0, 'D': 0, 'E': 0, 'F': 0, 'G': 0, 'H': 0}
        self.restrictions = {'A': (-4096, 4096), 'B': (-4096, 4096), 'C': (-4096, 4096), 'D': (-4096, 4096),
                             'E': (-4096, 4096), 'F': (-4096, 4096), 'G': (-4096, 4096), 'H': (-4096, 4096)}
        self.dU = 100

    def send(self, lit, sign):
        if self.restrictions[lit][0] < self.current_pos[lit] + sign * self.dU < self.restrictions[lit][1]:
            self.ser.write((self.names_def[lit] + str(sign * self.dU).rjust(4, '0')).encode())
            self.current_pos[lit] += sign * self.dU

    def on_L1_press(self):
        self.L1_on = True

    def on_L1_release(self):
        self.L1_on = False

    def on_L2_press(self, value):
        self.L2_on = True

    def on_L2_release(self):
        self.L2_on = False

    def on_R1_press(self):
        self.R1_on = True

    def on_R1_release(self):
        self.R1_on = False

    def on_R2_press(self, value):
        self.R2_on = True

    def on_R2_release(self):
        self.R2_on = False

    def on_x_press(self):
        if self.R1_on:
            self.send('B', 1)
        elif self.L1_on:
            self.send('F', -1)
        else:
            self.send('F', -1)
            self.send('B', -1)

    def on_triangle_press(self):
        if self.R1_on:
            self.send('B', -1)
        elif self.L1_on:
            self.send('F', 1)
        else:
            self.send('F', 1)
            self.send('B', 1)

    def on_circle_press(self):
        if self.R1_on:
            self.send('C', 1)
        elif self.L1_on:
            self.send('G', -1)
        else:
            self.send('G', -1)
            self.send('C', -1)

    def on_square_press(self):
        if self.R1_on:
            self.send('C', -1)
        elif self.L1_on:
            self.send('G', 1)
        else:
            self.send('G', 1)
            self.send('C', 1)

    def on_up_arrow_press(self):
        if self.R1_on:
            self.send('A', -1)
        elif self.L1_on:
            self.send('E', 1)
        else:
            self.send('E', 1)
            self.send('A', 1)

    def on_down_arrow_press(self):
        if self.R1_on:
            self.send('A', 1)
        elif self.L1_on:
            self.send('E', -1)
        else:
            self.send('E', -1)
            self.send('A', -1)

    def on_left_arrow_press(self):
        if self.R1_on:
            self.send('D', -1)
        elif self.L1_on:
            self.send('H', 1)
        else:
            self.send('H', 1)
            self.send('D', 1)

    def on_right_arrow_press(self):
        if self.R1_on:
            self.send('D', 1)
        elif self.L1_on:
            self.send('H', -1)
        else:
            self.send('H', -1)
            self.send('D', -1)


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