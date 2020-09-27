#include "AccelerometerFrame.h"

#include <boost/exception/diagnostic_information.hpp>
#include <ros/console.h>

Interface::DownstreamData::AccelerometerFrame::AccelerometerFrame()
{
    potocolIndentificator = "AccelerometerFrame";
    stIdentifier = 0x04;
}

Interface::DownstreamData::AccelerometerFrame::~AccelerometerFrame()
{

}

std::vector<uint8_t> Interface::DownstreamData::AccelerometerFrame::serialize()
{
    std::vector<uint8_t> output(3);


    output[0] = stIdentifier;
    output[1] = registryAddress;
    output[2] = registryValue;

    return output;
}

void Interface::DownstreamData::AccelerometerFrame::deserialize(boost::property_tree::ptree& pt)
{
    try
    {
        registryAddress = pt.get<int>("AccelerometerFrame.RegistryAddress");
        registryValue = pt.get<int>("AccelerometerFrame.RegistryValue");
    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        ROS_ERROR("Bad IMU frame received. Boost says: %s", diag.c_str());
    }

}

void Interface::DownstreamData::AccelerometerFrame::doTheProcessing()
{

}


