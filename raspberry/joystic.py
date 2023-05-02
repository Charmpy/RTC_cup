from pyPS4Controller.controller import Controller
import serial
from time import sleep


class MyController(Controller):
    def __init__(self, **kwargs):
        Controller.__init__(self, **kwargs)
        # self.ser = serial.Serial ("/dev/ttyACM0", 57600)

    def on_L3_y_at_rest(self):
        pass

    # self.ser.write(('A' + str(2048)).encode())
    def on_R3_y_at_rest(self):
        # self.ser.write(('B' + str(2048)).encode())
        pass

    def on_L3_down(self, value):
        print(str(2048 - int(value / 16)).rjust(4, '0'))
        # self.ser.write(('A' + str(2048 - int(value/16)).rjust(4, '0')).encode())

    def on_L3_up(self, value):
        print(str(2048 - int(value / 16)).rjust(4, '0'))
        # self.ser.write(('A' + str(2048 - int(value/16)).rjust(4, '0')).encode())

    def on_R3_up(self, value):
        print(str(2048 - int(value / 16)).rjust(4, '0'))
        self.ser.write(('B' + str(2048 - int(value / 16)).rjust(4, '0')).encode())

    def on_R3_down(self, value):
        print(str(2048 - int(value / 16)).rjust(4, '0'))
        self.ser.write(('B' + str(2048 - int(value / 16)).rjust(4, '0')).encode())

    def on_x_press(self):
        # self.ser.write(('A' + str(4095)).encode())
        pass

    def on_x_release(self):
        # self.ser.write(('A' + str(2048)).encode())
        pass

    def on_circle_press(self):
        # self.ser.write(('B' + str(4095)).encode())
        pass

    def on_circle_release(self):
        # self.ser.write(('B' + str(2048)).encode())
        pass

    ## https://github.com/ArturSpirin/pyPS4Controller