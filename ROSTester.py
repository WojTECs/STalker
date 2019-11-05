#!/usr/bin/env python

import rospy
import time
from std_msgs.msg import String

def talker():
    pub = rospy.Publisher('STalkerIn', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(1) # 10hz
    while not rospy.is_shutdown():
        hello_str = "{ \"MovementFrameTurnPropulsion\": { \"turnDirection\": \"1\", \"propulsionDirection\": \"1\", \"turnValue\": \"500\", \"propulsionValue\": \"400\", \"timeToDrive\": \"3000\", \"isQueued\": \"true\"  }} "
        rospy.loginfo(hello_str)
        pub.publish(hello_str)
        time.sleep( 2 )
        
        hello_str = "{ \"MovementFrameTurnPropulsion\": { \"turnDirection\": \"0\", \"propulsionDirection\": \"0\", \"turnValue\": \"000\", \"propulsionValue\": \"000\", \"timeToDrive\": \"3000\", \"isQueued\": \"true\"    }} "
        rospy.loginfo(hello_str)
        pub.publish(hello_str)
        time.sleep( 2 )

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
