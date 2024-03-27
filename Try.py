import serial
import time
from cvzone.SerialModule import SerialObject

aruduino  = SerialObject(portNo='/dev/cu.usbserial-56CA0018311', baudRate=115200)

#ser = serial.Serial(port="/dev/cu.usbserial-56CA0018311", baudrate=115200)


for i in range(100):

    aruduino.sendData([1])
    time.sleep(2)
    aruduino.sendData([0])
    time.sleep(1)
