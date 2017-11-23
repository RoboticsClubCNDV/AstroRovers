#including necessary libraries
from sense_hat import SenseHat
import math
import serial

#using the functions for all the sensors
sense = SenseHat()
humidity = sense.get_humidity()
temp = sense.get_temperature()-10
pressure = sense.get_pressure()/1000
altitude = 44330*(1-pow(pressure/1000, 1/525.55))
ser = serial.Serial('/dev/ttyUSB0', 9600) #used for the connection with Arduino

""" Receiving data from the user
Raspberry Pi:
    H - humidity
    T - temperature
    P - pressure
    E - altitude
Arduino:
    L & O - servomotor controls
    W, A, S, D - rover movement
    X - stopping movement
    C - carbon monoxide
    M - methane """

while True:
    data = raw_input('Show: ')

    if data == 'H' or data == 'h':
        print("Humidity: %s %%rH" % humidity)
    
    if data == 'T' or data == 't':
        print("Temperature: %s C" % temp)
    
    if data == 'P' or data == 'p':
        print("Pressure: %s Bars" % pressure)

    if data == 'E' or data == 'e':
        print("Altitude: %s Meters" % altitude)
    if(data == 'L' or data == 'l'):
        ser.write('L')
    if(data == 'O' or data == 'o'):
        ser.write('O')
    if(data == 'Y' or data == 'y'):
        ser.write('Y')
    if(data == 'U' or data == 'u'):
        ser.write('U')
    if(data == 'W' or data == 'w'):
        ser.write('W')
    if(data == 'S' or data == 's'):
        ser.write('S')
    if(data == 'A' or data == 'a'):
        ser.write('A')
    if(data == 'D' or data == 'd'):
        ser.write('D')
    if(data == 'C' or data == 'c'):
        ser.write('C')
        read_ser=ser.readline();
        print(read_ser);
    if(data == 'M' or data == 'm'):
        ser.write('M')
        read_ser=ser.readline();
        print(read_ser);
    if(data == 'X' or data == 'x'):
        ser.write('X')
