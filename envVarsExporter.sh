#/bin/bash

me=`basename "$0"` #get the name of the script

#if file contains source #thisScript dont do anything, if not then append
if !(grep -q "source $(pwd)/$me" "/home/$USER/.bashrc"); then
    echo "source $(pwd)/$me" >> "/home/$USER/.bashrc"
    echo "File souced itself in the ~/.bashrc file"
fi

if (test -f "/home/$USER/ROS_MASTER_URI.env"); then
    export ROS_MASTER_URI="$(cat /home/$USER/ROS_MASTER_URI.env)"
else
    echo "http://<system_with_roscore_ip>:11311" > "/home/$USER/ROS_MASTER_URI.env"
    echo "Check /home/$USER/ROS_MASTER_URI.env file and restart bash"
fi

if (test -f "/home/$USER/ROS_HOSTNAME.env"); then
    export ROS_HOSTNAME="$(cat /home/$USER/ROS_HOSTNAME.env)"
    export ROS_IP="$(cat /home/$USER/ROS_HOSTNAME.env)"
else
    echo "<your_host_ip>" > "/home/$USER/ROS_HOSTNAME.env"
    echo "Check /home/$USER/ROS_HOSTNAME.env file and restart bash"
fi
