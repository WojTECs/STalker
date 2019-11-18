#pragma once

#include <vector>
#include <memory>

#include "ros/ros.h"
#include "std_msgs/String.h"

#include "../DataExchanged/DownstreamDataType.h"
#include "../DataExchanged/UpstreamDataType.h"
#include "../STInterface/STInterfaceClientTCP.h"
#include "../STInterface/STInterfaceClientUDP.h"

namespace STInterface
{
    class STInterfaceClientTCP;
    class STInterfaceClientUDP;
}

namespace ROSInterface
{

class ROSInterfaceClient
{
private:

    std::shared_ptr<STInterface::STInterfaceClientTCP> STTCPClient;
    std::shared_ptr<STInterface::STInterfaceClientUDP> STUDPClient;
    std::list<std::unique_ptr<Interface::DownstreamDataType>> expectedDataTypes;

    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber;

    ros::AsyncSpinner spinner;

    std::map<std::string, ros::Publisher> rosPublishers;
    std::map<std::string, ros::Publisher>::iterator rosPublisherIndex;

public:
    void setSTTCPInterface(std::shared_ptr<STInterface::STInterfaceClientTCP> client);
    void setSTUDPInterface(std::shared_ptr<STInterface::STInterfaceClientUDP> client);

    //Adds >>REFERENCE<< for the object in the internal list of expected data types.
    void addExpectedDataType(std::unique_ptr<Interface::DownstreamDataType> iExpectedDataType);
    //Necessary to call to empty the list of expected data types. Not calling may result in SIGABRT!.
    void clear();
    void receiveMessageCallback(const std_msgs::String::ConstPtr& msg);
    void publishData(std::string iData, std::string rosTopic);

    ROSInterfaceClient();
    virtual ~ROSInterfaceClient();

};

} //namespace STInterface
