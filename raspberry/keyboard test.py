import sys, select, os
import msvcrt
import tty, termiosdbjvxnlnl.

msg = """
Control robot
---------------------------
Moving around:
   q    w    e
   a    s    d
        x
w/x : increase/decrease linear X velocity 
a/d : increase/decrease angular velocity 
q/e : increase/decreace linear Y velocity
space key, s : force stop
CTRL-C to quit
"""

e = """
Communications Failed
"""

def getKey():
    if os.name == 'nt':
      return msvcrt.getch()

    tty.setraw(sys.stdin.fileno())
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ''

    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key




if __name__=="__main__":
    settings = termios.tcgetattr(sys.stdin)
    servo_1 = 0
    servo_2 = 0
    try:
        print(msg)
        while(1):
            key = getKey()
            if key == 'w' :
                servo_1 = 10

            elif key == 's':
                servo_1 -= 10
            else:
                if (key == '\x03'):
                    break
            if status == 20 :
                print(msg)
                status = 0


    except Exception as eq:
        print(eq)

    finally:
        print(servo_1)
