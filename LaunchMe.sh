#/bin/bash
#This is a script used to launch ROS and STalker on a remote system(RPI, NVidia or Odroid)
source /opt/ros/melodic/setup.bash
killall roscore
killall STalkerApplicationExample
sleep 5 && ./STalkerExampleApplication/STalkerApplicationExample &
roscore
