#include "MovementOrderLeftRightFrame.h"

#include <boost/exception/diagnostic_information.hpp>
#include <ros/console.h>

Interface::DownstreamData::MovementOrderLeftRightFrame::MovementOrderLeftRightFrame()
{
    potocolIndentificator = "MovementFrame";
}

Interface::DownstreamData::MovementOrderLeftRightFrame::~MovementOrderLeftRightFrame()
{

}

std::vector<uint8_t> Interface::DownstreamData::MovementOrderLeftRightFrame::serialize()
{
    std::vector<uint8_t> output(7);

    output[0] = 0x04;//ID
    output[1] = leftDirection << 4 || rightDirection;
    output[2] = leftSidePWM >> 8;
    output[3] = leftSidePWM & 0xFF;
    output[4] = rightSidePWM >> 8;
    output[5] = rightSidePWM & 0xFF;
    output[6] = timeToDrive >> 8;

    return output;
}

void Interface::DownstreamData::MovementOrderLeftRightFrame::deserialize(boost::property_tree::ptree& pt)
{
    try
    {
        leftDirection = pt.get<int>("MovementFrameLeftRight.leftDirection");
        rightDirection = pt.get<int>("MovementFrameLeftRight.rightDirection");
        leftSidePWM = pt.get<int>("MovementFrameLeftRight.leftSidePWM");
        rightSidePWM = pt.get<int>("MovementFrameLeftRight.rightSidePWM");
        timeToDrive = pt.get<int>("MovementFrameTurnPropulsion.timeToDrive");

    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        ROS_ERROR("Bad Movement frame received. Boost says: %s", diag.c_str());
    }
}

void Interface::DownstreamData::MovementOrderLeftRightFrame::doTheProcessing()
{

}
