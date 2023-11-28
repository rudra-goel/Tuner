import board
import digitalio
import time
import analogio


led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

pin = analogio.AnalogIn(board.A2)

def getVoltage(val):
    return (val*3.3)/65536

while True:
    led.value=False
    voltage = getVoltage(pin.value)
    if voltage > 1.7:
        print(voltage)
        led.value=True
    time.sleep(.01)