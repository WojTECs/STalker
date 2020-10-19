#include "ElectromagnesFrame.h"

#include <boost/exception/diagnostic_information.hpp>
#include <ros/console.h>

Interface::DownstreamData::ElectromagnesFrame::ElectromagnesFrame()
{
    potocolIndentificator = "ElectromagnesFrame";
    stIdentifier = 0x10;
}

Interface::DownstreamData::ElectromagnesFrame::~ElectromagnesFrame()
{

}

std::vector<uint8_t> Interface::DownstreamData::ElectromagnesFrame::serialize()
{
    std::vector<uint8_t> output(3);


    output[0] = stIdentifier;
    output[1] = value;

    return output;
}

void Interface::DownstreamData::ElectromagnesFrame::deserialize(const uint16_t *msgArray, uint16_t arraySize)
{
//    try
//    {
//        value = pt.get<int>("ElectromagnesFrame.value");
//    }
//    catch (const boost::exception& e)
//    {
//        std::string diag = diagnostic_information(e);
//        ROS_ERROR("Bad IMU frame received. Boost says: %s", diag.c_str());
//    }

    value = msgArray[0];
}

void Interface::DownstreamData::ElectromagnesFrame::doTheProcessing()
{

}


