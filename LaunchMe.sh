#/bin/bash
source /opt/ros/melodic/setup.bash
killall roscore
killall STalkerApplicationExample
sleep 5 && ./STalkerExampleApplication/STalkerApplicationExample &
roscore
