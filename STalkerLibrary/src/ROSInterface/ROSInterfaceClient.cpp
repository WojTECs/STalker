#include "ROSInterfaceClient.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <ros/console.h>


void ROSInterface::ROSInterfaceClient::setSTTCPInterface(std::shared_ptr<STInterface::STInterfaceClientTCP> client)
{
    STTCPClient = client;
}

void ROSInterface::ROSInterfaceClient::setSTUDPInterface(std::shared_ptr<STInterface::STInterfaceClientUDP> client)
{
    STUDPClient = client;
}

void ROSInterface::ROSInterfaceClient::addExpectedDataType(std::unique_ptr<Interface::DownstreamDataType> iExpectedDataType)
{
//    expectedDataTypes.push_back(std::move(iExpectedDataType));
//    ROS_DEBUG("ROS Interface enlisted new data type");
    if(expectedDataTypes[iExpectedDataType->getProtocolIdentificator()]!=nullptr)
    {
        ROS_WARN("Error during enlisting new message type. This message ID is already occupied!");
    }
    expectedDataTypes[iExpectedDataType->getProtocolIdentificator()] = std::move(iExpectedDataType);
    ROS_DEBUG("STInterface session enlisted new data type");

}

//void ROSInterface::ROSInterfaceClient::clear()
//{
//    expectedDataTypes.clear();
//    ROS_DEBUG("ROS Interface cleared expected data types list");
//}

//void ROSInterface::ROSInterfaceClient::receiveMessageCallback(const std_msgs::String::ConstPtr& msg)
//{

//    std::stringstream ss;
//    ss << msg->data.c_str();

//    boost::property_tree::ptree pt;

//    try
//    {
//        boost::property_tree::read_json(ss, pt);
//    }
//    catch (const boost::exception& e)
//    {
//        std::string diag = diagnostic_information(e);
//        ROS_ERROR("Probably received broken JSON. Boost says: %s", diag.c_str());

//    }

//    for (auto ExpectedDataTypeIterator = expectedDataTypes.begin(); ExpectedDataTypeIterator != expectedDataTypes.end(); ExpectedDataTypeIterator++)
//    {
//        if(pt.get_child_optional(ExpectedDataTypeIterator->get()->getProtocolIdentificator()))
//        {
//            ExpectedDataTypeIterator->get()->deserialize(pt);
//            ExpectedDataTypeIterator->get()->doTheProcessing();
//            //#TODO switch interface type
//            STUDPClient->publishData(*ExpectedDataTypeIterator->get());
//        }
//    }
//}

void ROSInterface::ROSInterfaceClient::receiveMessageCallback(const std_msgs::UInt16MultiArray::ConstPtr& msg)
{
    uint8_t cmdID = msg->data[0];

    expectedDataTypes[cmdID]->deserialize(&(msg->data[1]), msg->data.size() - 1);
    expectedDataTypes[cmdID]->doTheProcessing();
    STUDPClient->publishData(*expectedDataTypes[cmdID]);
}

void ROSInterface::ROSInterfaceClient::publishString(std::string iData, std::string rosTopic)
{    

    std_msgs::String message;
    message.data  = iData;

    //Publisher for this topic isn't created yet
    rosPublisherIndex = rosPublishers.find(rosTopic);
    if (rosPublisherIndex == rosPublishers.end())
    {
        rosPublishers[rosTopic] = nodeHandle.advertise<std_msgs::String>(rosTopic, 1000);

    }
    else
    {
        rosPublisherIndex->second.publish(message);
    }


}

void ROSInterface::ROSInterfaceClient::publishFloat64Array(std_msgs::Float64MultiArray array, std::string rosTopic)
{
    rosPublisherIndex = rosPublishers.find(rosTopic);
    if (rosPublisherIndex == rosPublishers.end())
    {
        rosPublishers[rosTopic] = nodeHandle.advertise<std_msgs::Float64MultiArray>(rosTopic, 1000);

    }
    else
    {
        rosPublisherIndex->second.publish(array);
    }
}

void ROSInterface::ROSInterfaceClient::publishUInt16Array(std_msgs::UInt16MultiArray array, std::string rosTopic)
{
    rosPublisherIndex = rosPublishers.find(rosTopic);
    if (rosPublisherIndex == rosPublishers.end())
    {
        rosPublishers[rosTopic] = nodeHandle.advertise<std_msgs::UInt16MultiArray>(rosTopic, 1000);

    }
    else
    {
        rosPublisherIndex->second.publish(array);
    }
}

void ROSInterface::ROSInterfaceClient::publishInt32Array(std_msgs::Int32MultiArray array, std::string rosTopic)
{
    rosPublisherIndex = rosPublishers.find(rosTopic);
    if (rosPublisherIndex == rosPublishers.end())
    {
        rosPublishers[rosTopic] = nodeHandle.advertise<std_msgs::Int32MultiArray>(rosTopic, 1000);

    }
    else
    {
        rosPublisherIndex->second.publish(array);
    }
}

void ROSInterface::ROSInterfaceClient::publishUInt8Array(std_msgs::UInt8MultiArray array, std::string rosTopic)
{
    rosPublisherIndex = rosPublishers.find(rosTopic);
    if (rosPublisherIndex == rosPublishers.end())
    {
        rosPublishers[rosTopic] = nodeHandle.advertise<std_msgs::UInt8MultiArray>(rosTopic, 1000);

    }
    else
    {
        rosPublisherIndex->second.publish(array);
    }
}

void ROSInterface::ROSInterfaceClient::publishUInt16(std_msgs::UInt16 input, std::string rosTopic)
{
    rosPublisherIndex = rosPublishers.find(rosTopic);
    if (rosPublisherIndex == rosPublishers.end())
    {
        rosPublishers[rosTopic] = nodeHandle.advertise<std_msgs::UInt16>(rosTopic, 1000);


    }
    else
    {
        rosPublisherIndex->second.publish(input);
    }
}

void ROSInterface::ROSInterfaceClient::publishUInt32(std_msgs::UInt32 input, std::string rosTopic)
{
    rosPublisherIndex = rosPublishers.find(rosTopic);
    if (rosPublisherIndex == rosPublishers.end())
    {
        rosPublishers[rosTopic] = nodeHandle.advertise<std_msgs::UInt32>(rosTopic, 1000);


    }
    else
    {
        rosPublisherIndex->second.publish(input);
    }
}

void ROSInterface::ROSInterfaceClient::publishUInt32Array(std_msgs::UInt32MultiArray array, std::string rosTopic)
{
    rosPublisherIndex = rosPublishers.find(rosTopic);
    if (rosPublisherIndex == rosPublishers.end())
    {
        rosPublishers[rosTopic] = nodeHandle.advertise<std_msgs::UInt32MultiArray>(rosTopic, 1000);

    }
    else
    {
        rosPublisherIndex->second.publish(array);
    }
}

void ROSInterface::ROSInterfaceClient::publishNavSatFix(sensor_msgs::NavSatFix input, std::string rosTopic)
{
    rosPublisherIndex = rosPublishers.find(rosTopic);
    if (rosPublisherIndex == rosPublishers.end())
    {
        rosPublishers[rosTopic] = nodeHandle.advertise<sensor_msgs::NavSatFix>(rosTopic, 1000);
    }
    else
    {
        rosPublisherIndex->second.publish(input);
    }
}

void ROSInterface::ROSInterfaceClient::publishLaserScan(sensor_msgs::LaserScan input, std::string rosTopic)
{
    rosPublisherIndex = rosPublishers.find(rosTopic);
    if (rosPublisherIndex == rosPublishers.end())
    {
        rosPublishers[rosTopic] = nodeHandle.advertise<sensor_msgs::LaserScan>(rosTopic, 1000);
    }
    else
    {
        rosPublisherIndex->second.publish(input);
    }
}

ROSInterface::ROSInterfaceClient::ROSInterfaceClient() :  spinner(0)
{
//    subscriber = nodeHandle.subscribe("STalkerIn", 1000, &ROSInterface::ROSInterfaceClient::receiveMessageCallback, this);
    subscriber = nodeHandle.subscribe("STalkerIn", 1000, &ROSInterface::ROSInterfaceClient::receiveMessageCallback, this);
    spinner.start();

    ROS_INFO("ROS Interface Client created");
}

ROSInterface::ROSInterfaceClient::~ROSInterfaceClient()
{

}
