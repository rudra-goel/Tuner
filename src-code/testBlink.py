import board
import digitalio
import time

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

def dash():
    led.value = True
    time.sleep(.5)
    led.value = False
    time.sleep(.1)


def dot():
    led.value = True
    time.sleep(.1)
    led.value = False
    time.sleep(.1)

while True:
    # led.value = True
    # time.sleep(0.5)
    # led.value = False
    # time.sleep(0.5)
    # print("BUSLEY IS SO HOT")
    dot()
    dash()
    dot()
    dash()
    time.sleep(1)


