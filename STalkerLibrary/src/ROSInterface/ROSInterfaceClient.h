#pragma once

#include <vector>
#include <memory>

#include "ros/ros.h"
#include "std_msgs/String.h"

#include "../DataExchanged/DownstreamDataType.h"
#include "../DataExchanged/UpstreamDataType.h"


namespace ROSInterface
{

class ROSInterfaceClient
{
private:

    static std::list<std::weak_ptr<Interface::DownstreamDataType>> expectedDataTypes;

    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber;

    ros::AsyncSpinner spinner;
    static ros::Publisher chatter_pub;

public:

    //Adds >>REFERENCE<< for the object in the internal list of expected data types.
    static void addExpectedDataType(const std::shared_ptr<Interface::DownstreamDataType>& iExpectedDataType);
    //Necessary to call to empty the list of expected data types. Not calling may result in SIGABRT!.
    static void clear();
    static void receiveMessageCallback(const std_msgs::String::ConstPtr& msg);
    static void publishData(Interface::UpstreamDataType& iData);

    ROSInterfaceClient();
    virtual ~ROSInterfaceClient();

};

} //namespace STInterface
