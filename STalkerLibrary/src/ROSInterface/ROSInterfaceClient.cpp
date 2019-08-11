#include "ROSInterfaceClient.h"
#include "../Logger/Logger.h"
#include "../Logger/Logger.h"
#include "../STInterface/STInterfaceClient.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/exception/diagnostic_information.hpp>


ros::Publisher ROSInterface::ROSInterfaceClient::chatter_pub = ros::Publisher();
std::list<std::weak_ptr<Interface::DownstreamDataType>> ROSInterface::ROSInterfaceClient::mExpectedDataTypes;


void ROSInterface::ROSInterfaceClient::addExpectedDataType(const std::shared_ptr<Interface::DownstreamDataType> &iExpectedDataType)
{
    mExpectedDataTypes.push_back(iExpectedDataType);
}

void ROSInterface::ROSInterfaceClient::clear()
{
    mExpectedDataTypes.clear();
}

void ROSInterface::ROSInterfaceClient::receiveMessageCallback(const std_msgs::String::ConstPtr& msg)
{

    std::stringstream ss;
    ss << msg->data.c_str();

    boost::property_tree::ptree pt;

    //#TODO catch exception from line below if json isn't valid enable_current_exception(enable_error_info(e));
    try
    {
         boost::property_tree::read_json(ss, pt);
    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        //#TODO log error

    }

    //#TODO - what if expected data type id or size == 0
    for (auto ExpectedDataTypeIterator = mExpectedDataTypes.begin(); ExpectedDataTypeIterator != mExpectedDataTypes.end(); ExpectedDataTypeIterator++)
    {
        //Checkup whether reference still exists
        std::shared_ptr<Interface::DownstreamDataType> ExpectedDataTypeSharedBond;
        ExpectedDataTypeSharedBond = ExpectedDataTypeIterator->lock();

        //if reference exists, and message type is correct
        if(ExpectedDataTypeSharedBond)
        {
            //if json trunk can be found
            if(pt.get_child_optional(ExpectedDataTypeSharedBond->getProtocolIdentificator()))
            {
                ExpectedDataTypeSharedBond->deserialize(pt);
                ExpectedDataTypeSharedBond->doTheProcessing();

                STInterface::STInterfaceClient::publishData(ExpectedDataTypeSharedBond->serialize());
            }
        }
        else
        {
            mExpectedDataTypes.erase(ExpectedDataTypeIterator);
        }
    }

    //#TODO remove
    //std::string = pt.get<std::string>("DataType");
//    if(pt.get_child_optional( "EncoderFrame"))
//    {
//     std::cout<<"Us";
//    }



}

void ROSInterface::ROSInterfaceClient::publishData(Interface::UpstreamDataType& iData)
{

    ros::Publisher chatter_pub = ros::NodeHandle().advertise<std_msgs::String>("STalkerOut", 1000);



    std::ostringstream pTreeToStringCatalizator;
    boost::property_tree::json_parser::write_json(pTreeToStringCatalizator, iData.serialize());

    std_msgs::String message;
    message.data  = pTreeToStringCatalizator.str();

    //#TODO -remove
    //message.data = "{ \"IMUFrame\": { \"RegistryAddress\": \"8995\", \"RegistryValue\": \"13364\" },\"RegistryAddress\": \"8995\" } ";

    ROSInterface::ROSInterfaceClient::chatter_pub.publish(message);

    //#TODO - solve the spinning problem to spin in a separate thread more frequently
    ros::spinOnce();

    ROS_INFO("%s", message.data.c_str());
}

ROSInterface::ROSInterfaceClient::ROSInterfaceClient()
    :
      spinner(0)
{
    ros::NodeHandle nodeHandle;
    ROSInterface::ROSInterfaceClient::chatter_pub = nodeHandle.advertise<std_msgs::String>("STalkerIn", 1000);


    mSubscriber = mNodeHandle.subscribe("chatter", 1000, receiveMessageCallback);

    spinner.start();
}

ROSInterface::ROSInterfaceClient::~ROSInterfaceClient()
{

}





