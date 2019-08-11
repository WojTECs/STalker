#!/usr/bin/env python

#STalker testing tool
#Use with rostopic echo STalkerOut
#
#To test incoming messages run:
#with netcat -l <port> and wireshark if necessary 

import socket

host = 'localhost'
port = 1228                 # The same port as used by the server skt.send('\x12\r')
s1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s3 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s4 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s5 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#what frames to test
testAll = True #stronger than test<specificFrame> vars


#vars for separate tests
testAccellerometer = False
testGyroscope = False
testMagnetometer = False
testPWM = False
testEncoder = False


if testAll or testAccellerometer :
    s1.connect((host, port))
    #Accellerometer frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
    s1.sendall(b'\x04\x1e\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x02\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x03\x02\x02\x03\x03\x0a\x0b\x0c\x0d') 
    s1.close()

if testAll or testGyroscope :
    s2.connect((host, port))
    #Gyroscope frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
    s2.sendall(b'\x05\x1e\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x02\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x03\x02\x02\x03\x03\x0a\x0b\x0c\x0d') 
    s2.close()

if testAll or testMagnetometer :
    s3.connect((host, port))
    #Magnetometer frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
    s3.sendall(b'\x06\x1e\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x02\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x03\x02\x02\x03\x03\x0a\x0b\x0c\x0d') 
    s3.close()

if testAll or testPWM :
    s4.connect((host, port))
    #PWM frame with no. of bytes, direction forward and four bytes describing PWM's of four motors(for each wheel)
    s4.sendall(b'\x02\x05\x01\x23\x23\x34\x34') 
    s4.close()

if testAll or testEncoder :
    s5.connect((host, port))
    #Encoder frame with no. of bytes, direction forward and four bytes describing spins on both sides
    s5.sendall(b'\x07\x04\x23\x23\x34\x34') 
    s5.close()









