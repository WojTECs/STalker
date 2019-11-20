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
    expectedDataTypes.push_back(std::move(iExpectedDataType));
    ROS_DEBUG("ROS Interface enlisted new data type");
}

void ROSInterface::ROSInterfaceClient::clear()
{
    expectedDataTypes.clear();
    ROS_DEBUG("ROS Interface cleared expected data types list");
}

void ROSInterface::ROSInterfaceClient::receiveMessageCallback(const std_msgs::String::ConstPtr& msg)
{

    std::stringstream ss;
    ss << msg->data.c_str();

    boost::property_tree::ptree pt;

    try
    {
        boost::property_tree::read_json(ss, pt);
    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        ROS_ERROR("Probably received broken JSON. Boost says: %s", diag.c_str());

    }

    for (auto ExpectedDataTypeIterator = expectedDataTypes.begin(); ExpectedDataTypeIterator != expectedDataTypes.end(); ExpectedDataTypeIterator++)
    {
        if(pt.get_child_optional(ExpectedDataTypeIterator->get()->getProtocolIdentificator()))
        {
            ExpectedDataTypeIterator->get()->deserialize(pt);
            ExpectedDataTypeIterator->get()->doTheProcessing();
            //#TODO switch interface type
            STUDPClient->publishData(*ExpectedDataTypeIterator->get());
        }
    }
}

void ROSInterface::ROSInterfaceClient::publishData(std::string iData, std::string rosTopic)
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

ROSInterface::ROSInterfaceClient::ROSInterfaceClient() :  spinner(0)
{
    subscriber = nodeHandle.subscribe("STalkerIn", 1000, &ROSInterface::ROSInterfaceClient::receiveMessageCallback, this);
    spinner.start();

    ROS_INFO("ROS Interface Client created");
}

ROSInterface::ROSInterfaceClient::~ROSInterfaceClient()
{

}
