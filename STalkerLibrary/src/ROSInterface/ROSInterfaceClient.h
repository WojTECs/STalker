#pragma once

#include <vector>
#include <memory>

#include "ros/ros.h"
#include "std_msgs/String.h"

#include "../DataExchanged/DownstreamDataType.h"
#include "../DataExchanged/UpstreamDataType.h"
#include "../STInterface/STInterfaceClient.h"

namespace STInterface
{
    class STInterfaceClient;
}

namespace ROSInterface
{

class ROSInterfaceClient
{
private:

    std::shared_ptr<STInterface::STInterfaceClient> STClient;
    std::list<std::unique_ptr<Interface::DownstreamDataType>> expectedDataTypes;

    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber;

    ros::AsyncSpinner spinner;
    static ros::Publisher chatter_pub;

public:
    void setSTInterface(std::shared_ptr<STInterface::STInterfaceClient> client);

    //Adds >>REFERENCE<< for the object in the internal list of expected data types.
    void addExpectedDataType(std::unique_ptr<Interface::DownstreamDataType> iExpectedDataType);
    //Necessary to call to empty the list of expected data types. Not calling may result in SIGABRT!.
    void clear();
    void receiveMessageCallback(const std_msgs::String::ConstPtr& msg);
    void publishData(Interface::UpstreamDataType& iData);

    ROSInterfaceClient();
    virtual ~ROSInterfaceClient();

};

} //namespace STInterface
