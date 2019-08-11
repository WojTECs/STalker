#!/usr/bin/env python

import rospy
import time
from std_msgs.msg import String

def talker():
    pub = rospy.Publisher('STalkerIn', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(1) # 10hz
    while not rospy.is_shutdown():
        hello_str = "{ \"IMUFrame\": { \"RegistryAddress\": \"8995\", \"RegistryValue\": \"13364\" },\"RegistryAddress\": \"8995\" } "
        rospy.loginfo(hello_str)
        pub.publish(hello_str)
        time.sleep( 2 )

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
