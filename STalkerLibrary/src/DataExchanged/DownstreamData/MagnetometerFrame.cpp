#include "MagnetometerFrame.h"

#include <boost/exception/diagnostic_information.hpp>
#include <ros/console.h>

Interface::DownstreamData::MagnetometerFrame::MagnetometerFrame()
{
    potocolIndentificator = "MagnetometerFrame";
    stIdentifier = 0x06;
}

Interface::DownstreamData::MagnetometerFrame::~MagnetometerFrame()
{

}

std::vector<uint8_t> Interface::DownstreamData::MagnetometerFrame::serialize()
{
    std::vector<uint8_t> output(3);


    output[0] = stIdentifier;
    output[1] = registryAddress;
    output[2] = registryValue;

    return output;
}

void Interface::DownstreamData::MagnetometerFrame::deserialize(const uint16_t *msgArray, uint16_t arraySize)
{
//    try
//    {
//        registryAddress = pt.get<int>("MagnetometerFrame.RegistryAddress");
//        registryValue = pt.get<int>("MagnetometerFrame.RegistryValue");
//    }
//    catch (const boost::exception& e)
//    {
//        std::string diag = diagnostic_information(e);
//        ROS_ERROR("Bad IMU frame received. Boost says: %s", diag.c_str());
//    }

    registryAddress = msgArray[0];
    registryValue = msgArray[1];
}

void Interface::DownstreamData::MagnetometerFrame::doTheProcessing()
{

}


