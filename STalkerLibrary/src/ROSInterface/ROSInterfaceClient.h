#pragma once

#include <vector>
#include <memory>

#include "../DataExchanged/DownstreamDataType.h"
#include "../DataExchanged/UpstreamDataType.h"

#include "../Logger/Logger.h"

#include "ros/ros.h"
#include "std_msgs/String.h"


namespace ROSInterface
{

class ROSInterfaceClient
{
private:
    static std::list<std::weak_ptr<Interface::DownstreamDataType>> mExpectedDataTypes;

    ros::NodeHandle mNodeHandle;
    ros::Subscriber mSubscriber;

    ros::AsyncSpinner spinner;
    static ros::Publisher chatter_pub;

public:
    //Adds >>REFERENCE<< for the object in the internal list of expected data types.
    static void addExpectedDataType(const std::shared_ptr<Interface::DownstreamDataType>& iExpectedDataType);
    //Necessary to call to empty the list of expected data types. Not calling may result in SIGABRT!.
    static void clear();



    //#TODO - dodaj metode initu listenera - teraz to robi konstruktor a to nie jest oczywiste
    int b;
    int a();




    static void receiveMessageCallback(const std_msgs::String::ConstPtr& msg);

    static void publishData(Interface::UpstreamDataType& iData);

    ROSInterfaceClient();
    virtual ~ROSInterfaceClient();
};

} //namespace STInterface
