import socket

host = 'localhost'
port = 1228                 # The same port as used by the server skt.send('\x12\r')
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect((host, port))
###Accellerometer frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
#s.sendall(b'\x04\x1e\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x02\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x03\x02\x02\x03\x03\x0a\x0b\x0c\x0d') 
###Gyroscope frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
#s.sendall(b'\x05\x1e\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x02\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x03\x02\x02\x03\x03\x0a\x0b\x0c\x0d') 
###Magnetometer frame with 30 bytes of 3 datasets 2B xAxis + 2B yAxis + 2B zAxis + 4B timestamp
#s.sendall(b'\x06\x1e\x01\x01\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x02\x02\x02\x03\x03\x0a\x0b\x0c\x0d\x01\x03\x02\x02\x03\x03\x0a\x0b\x0c\x0d') 
###PWM frame with no. of bytes, direction forward and four bytes describing PWM's of four motors(for each wheel)
#s.sendall(b'\x02\x05\x01\x23\x23\x34\x34') 
###Encoder frame with no. of bytes, direction forward and four bytes describing spins on both sides
s.sendall(b'\x07\x04\x23\x23\x34\x34') 
data = s.recv(1024)
s.close()
print('Received', repr(data)) 

