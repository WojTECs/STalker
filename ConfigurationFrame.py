#!/usr/bin/env python

import rospy
import time
from std_msgs.msg import String

def talker():
    pub = rospy.Publisher('STalkerIn', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(100) # 10hz
    
    while not rospy.is_shutdown():
    
        hello_str = "{ \"MainConfigurationFrame\": { \"AccelerometerFrame\": \"1\", \"ContinentalLIDARDistanceFrame\": \"1\", \"ContinentalLIDARReflectionFrame\": \"1\", \"ContinentalLIDARSpeedFrame\": \"1\", \"EncoderFrame\": \"1\", \"GPSFrame\": \"1\", \"GyroscopeFrame\": \"1\", \"LidarFrame\": \"1\", \"MagnetometerFrame\": \"1\", \"MovementInformationFrame\": \"1\", \"PackageStatisticsFrame\": \"1\", \"RFIDFrame\": \"1\", \"ServiceTimeFrame\": \"1\", \"TimersFrame\": \"1\", \"TimeSyncFrame\": \"1\" }} "
        rospy.loginfo(hello_str)
        pub.publish(hello_str)
        time.sleep( 0.01 )
        
        
        #hello_str = "{ \"MovementFrameTurnPropulsion\": { \"turnDirection\": \"0\", ##\"propulsionDirection\": \"0\", \"turnValue\": \"000\", \"propulsionValue\": \"000\", \"timeToDrive\": \"3000\", \"isQueued\": \"false\"    }} "
        #rospy.loginfo(hello_str)
        #pub.publish(hello_str)
        #time.sleep( 2 )
        
        
        

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
