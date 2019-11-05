#!/usr/bin/env python

#STalker testing tool
#Use with rostopic echo STalkerOut
#
#To test incoming messages run:
#with netcat -l <port> and wireshark if necessary

import socket

host = 'localhost'
port = 1112                 # The same port as used by the server skt.send('\x12\r')
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#what frames to test
testAll = False #stronger than test<specificFrame> vars

testMultiframe = True

#vars for separate tests
testAccellerometer = False
testGyroscope = False
testMagnetometer = False
testPWM = False
testEncoder = False


if testAll or testMultiframe :
    s.connect((host, port))
    #Accellerometer frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp and 
    #Gyroscope frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
    #then Accellerometer again
    s.sendall(   b'\x04\x1e'
                +b'\x01\x01\x02\x01\x03\x03\x0a\x0b\x0c\x0d'
                +b'\x01\x02\x02\x01\x03\x03\x0a\x0b\x0c\x0d'
                +b'\x01\x03\x02\x01\x03\x03\x0a\x0b\x0c\x0d'
                +b'\x05\x1e'
                +b'\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d'
                +b'\x01\x02\x02\x02\x03\x03\x0a\x0b\x0c\x0d'
                +b'\x01\x03\x02\x02\x03\x03\x0a\x0b\x0c\x0d'
                +b'\x04\x1e'
                +b'\x01\x01\x02\x03\x03\x03\x0a\x0b\x0c\x0d'
                +b'\x01\x02\x02\x03\x03\x03\x0a\x0b\x0c\x0d'
                +b'\x01\x03\x02\x03\x03\x03\x0a\x0b\x0c\x0d')
    s.close()

if testAll or testAccellerometer :
    s.connect((host, port))
    #Accellerometer frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
    s.sendall(b'\x04\x1e\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x02\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x03\x02\x02\x03\x03\x0a\x0b\x0c\x0d')
    s.close()

if testAll or testGyroscope :
    s.connect((host, port))
    #Gyroscope frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
    s.sendall(b'\x05\x1e\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x02\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x03\x02\x02\x03\x03\x0a\x0b\x0c\x0d')
    s.close()

if testAll or testMagnetometer :
    s.connect((host, port))
    #Magnetometer frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
    s.sendall(b'\x06\x1e\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x02\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x03\x02\x02\x03\x03\x0a\x0b\x0c\x0d')
    s.close()

if testAll or testPWM :
    s.connect((host, port))
    #PWM frame with no. of bytes, direction forward and four bytes describing PWM's of four motors(for each wheel)
    s.sendall(b'\x02\x05\x01\x23\x23\x34\x34')
    s.close()

if testAll or testEncoder :
    s.connect((host, port))
    #Encoder frame with no. of bytes, direction forward and four bytes describing spins on both sides
    s.sendall(b'\x07\x04\x23\x23\x34\x34')
    s.close()
