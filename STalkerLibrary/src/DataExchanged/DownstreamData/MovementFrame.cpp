#include "MovementFrame.h"

#include <boost/exception/diagnostic_information.hpp>
#include <ros/console.h>

Interface::DownstreamData::MovementFrame::MovementFrame()
{
    potocolIndentificator = "MovementFrame";
}

Interface::DownstreamData::MovementFrame::~MovementFrame()
{

}

std::vector<uint8_t> Interface::DownstreamData::MovementFrame::serialize()
{
    std::vector<uint8_t> output(6);

    output[0] = 0x04;//ID
    output[1] = movementDirection;
    output[2] = leftSidePWM>>8;
    output[3] = leftSidePWM%256;
    output[4] = rightSidePWM>>8;
    output[5] = rightSidePWM%256;

    return output;
}

void Interface::DownstreamData::MovementFrame::deserialize(boost::property_tree::ptree& pt)
{
    try
    {
        movementDirection = pt.get<int>("MovementFrame.movementDirection");
        leftSidePWM = pt.get<int>("MovementFrame.leftSidePWM");
        rightSidePWM = pt.get<int>("MovementFrame.rightSidePWM");

    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        ROS_ERROR("Bad Movement frame received. Boost says: %s", diag.c_str());
    }
}

void Interface::DownstreamData::MovementFrame::doTheProcessing()
{

}


