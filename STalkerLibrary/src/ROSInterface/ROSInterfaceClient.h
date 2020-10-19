#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/UInt16MultiArray.h"
#include "std_msgs/UInt32MultiArray.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/UInt16.h"
#include "std_msgs/UInt32.h"
#include "sensor_msgs/NavSatFix.h"
#include "sensor_msgs/Range.h"
#include "sensor_msgs/LaserScan.h"

#include "../DataExchanged/DownstreamDataType.h"
#include "../DataExchanged/UpstreamDataType.h"
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
    std::unique_ptr<Interface::DownstreamDataType> expectedDataTypes[256];

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
//    void clear();
    void receiveMessageCallback(const std_msgs::UInt16MultiArray::ConstPtr& msg);
    void publishString(std::string iData, std::string rosTopic);
    void publishFloat64Array(std_msgs::Float64MultiArray array, std::string rosTopic);
    void publishUInt16Array(std_msgs::UInt16MultiArray array, std::string rosTopic);
    void publishInt32Array(std_msgs::Int32MultiArray array, std::string rosTopic);
    void publishUInt8Array(std_msgs::UInt8MultiArray array, std::string rostopic);
    void publishUInt16(std_msgs::UInt16 input, std::string rosTopic);
    void publishUInt32(std_msgs::UInt32 input, std::string rosTopic);
    void publishUInt32Array(std_msgs::UInt32MultiArray array, std::string rosTopic);
    void publishNavSatFix(sensor_msgs::NavSatFix input, std::string rosTopic);
    void publishLaserScan(sensor_msgs::LaserScan input, std::string rosTopic);
    void publishRange(sensor_msgs::Range input, std::string rosTopic);

    ROSInterfaceClient();
    virtual ~ROSInterfaceClient();

};

} //namespace STInterface
