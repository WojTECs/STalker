#include "GyroscopeFrame.h"

#include <boost/exception/diagnostic_information.hpp>
#include <ros/console.h>

Interface::DownstreamData::GyroscopeFrame::GyroscopeFrame()
{
    potocolIndentificator = "GyroscopeFrame";
    stIdentifier = 0x05;
}

Interface::DownstreamData::GyroscopeFrame::~GyroscopeFrame()
{

}

std::vector<uint8_t> Interface::DownstreamData::GyroscopeFrame::serialize()
{
    std::vector<uint8_t> output(3);


    output[0] = stIdentifier;
    output[1] = registryAddress;
    output[2] = registryValue;

    return output;
}

void Interface::DownstreamData::GyroscopeFrame::deserialize(boost::property_tree::ptree& pt)
{
    try
    {
        registryAddress = pt.get<int>("GyroscopeFrame.RegistryAddress");
        registryValue = pt.get<int>("GyroscopeFrame.RegistryValue");
    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        ROS_ERROR("Bad IMU frame received. Boost says: %s", diag.c_str());
    }

}

void Interface::DownstreamData::GyroscopeFrame::doTheProcessing()
{

}


