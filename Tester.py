#!/usr/bin/env python
import os
import socket
from time import sleep

host = 'localhost'
port = 1115   
useTCP = False #Default UDP



def main():
    
    menu = {}
    menu['a']="  Send upframe AccelerometerFrame" 
    menu['y']="  Send upframe GyroscopeFrame" 
    menu['m']="  Send upframe MagnetometerFrame"
    
    menu['d']="  Send upframe ContinentalLIDARDistanceFrame" 
    menu['r']="  Send upframe ContinentalLIDARReflectionFrame" 
    menu['s']="  Send upframe ContinentalLIDARSpeedFrame" 
    menu['e']="  Send upframe EncoderFrame" 
    menu['g']="  Send upframe GPSFrame" 
    
    menu['l']="  Send upframe LidarFrame" 
    menu['o']="  Send upframe MovementInformationFrame" 
    menu['p']="  Send upframe PackageStatisticsFrame" 
    menu['f']="  Send upframe RFIDFrame" 
    menu['v']="  Send upframe ServiceTimeFrame" 
    
    menu['t']="  Send upframe TimersFrame" 
    menu['i']="  Send upframe TimeSyncFrame" 
    menu['da']=" Send downframe AccelerometerFrame" 
    menu['de']=" Send downframe ElectromagnesFrame" 
    menu['dg']=" Send downframe GyroscopeFrame" 
    
    menu['dm']=" Send downframe MagnetometerFrame" 
    menu['dc']=" Send downframe MainConfigurationFrame" 
    menu['do']=" Send downframe MovementFrame" 
    menu['dot']="Send downframe MovementFrameTurnPropulsion" 
    menu['dt']=" Send downframe TimerConfigurationFrame" 
    
    menu['q']="  Exit"

    while True: 
        options=menu.keys()
        print '---------------------------------------------'
        print 'Connecting to host'
        socket = connect(host, port)
        print '---------------------------------------------'
        for entry in options: 
            print entry, menu[entry]
        print '---------------------------------------------'
        selection=raw_input("Please Select:") 
        
        
        if selection =='a': 
            print "Sending upstream AccelerometerFrame" 
            sendUpframeAccellerometer(socket)
         
        if selection =='y': 
            print "Sending upstream GyroscopeFrame" 
            sendUpframeGyroscope(socket)
        
        if selection =='m': 
            print "Sending upstream MagnetometerFrame" 
            sendUpframeMagnetometer(socket)
        
        
        
        elif selection == 'ua': 
            print "downframe AccelerometerFrame"
        elif selection == 'q': 
            break
        else: 
            print "Unknown Option Selected!" 
            

def connect(host, port):
    if useTCP :
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    else :
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect((host, port))
    return s
    
def sendUpframeAccellerometer(socket):
    #Accellerometer frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
    socket.sendall(b'\x04\x03'
                   '\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d'
                   '\x3a\x3a\x02\x02\x03\x03\x0a\x0b\x0c\x0d'
                   '\xff\xff\x02\x02\x03\x03\x0a\x0b\x0c\x0d')
    sleep(1)
    
def sendUpframeGyroscope(socket):
    #Gyroscope frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
    socket.sendall(b'\x05\x03'
                   '\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d'
                   '\x3a\x3a\x02\x02\x03\x03\x0a\x0b\x0c\x0d'
                   '\xff\xff\x02\x02\x03\x03\x0a\x0b\x0c\x0d')
    sleep(1)
    
def sendUpframeMagnetometer(socket):
    #Magnetometer frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
    socket.sendall(b'\x06\x03'
                   '\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d'
                   '\x3a\x3a\x02\x02\x03\x03\x0a\x0b\x0c\x0d'
                   '\xff\xff\x02\x02\x03\x03\x0a\x0b\x0c\x0d')
    sleep(1)
   
def sendUpframeMagnetometer(socket):
    #Magnetometer frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
    socket.sendall(b'\x06\x03'
                   '\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d'
                   '\x3a\x3a\x02\x02\x03\x03\x0a\x0b\x0c\x0d'
                   '\xff\xff\x02\x02\x03\x03\x0a\x0b\x0c\x0d')
    sleep(1)
   
   
def sendUpframeContinentalLIDARDistanceFrame(socket):
    #Accellerometer frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
    socket.sendall(b'\x04\x03'
                   '\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d'
                   '\x3a\x3a\x02\x02\x03\x03\x0a\x0b\x0c\x0d'
                   '\xff\xff\x02\x02\x03\x03\x0a\x0b\x0c\x0d')
    sleep(1)
main()



