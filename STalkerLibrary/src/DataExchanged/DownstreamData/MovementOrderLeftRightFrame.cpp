#include "MovementOrderLeftRightFrame.h"

#include <boost/exception/diagnostic_information.hpp>
#include <ros/console.h>

Interface::DownstreamData::MovementOrderLeftRightFrame::MovementOrderLeftRightFrame()
{
    stIdentifier = 0x02;
    potocolIndentificator = "MovementFrame";
}

Interface::DownstreamData::MovementOrderLeftRightFrame::~MovementOrderLeftRightFrame()
{

}

std::vector<uint8_t> Interface::DownstreamData::MovementOrderLeftRightFrame::serialize()
{
    std::vector<uint8_t> output(9);

    output[0] = stIdentifier; //ID
    output[1] = (leftDirection << 4) | (rightDirection & 0x0F);
    output[2] = leftSidePWM >> 8;
    output[3] = leftSidePWM & 0xFF;
    output[4] = rightSidePWM >> 8;
    output[5] = rightSidePWM & 0xFF;
    output[6] = timeToDrive >> 8;
    output[7] = timeToDrive & 0xFF;
    output[8] = shallQueue;


    return output;
}

void Interface::DownstreamData::MovementOrderLeftRightFrame::deserialize(const uint16_t *msgArray, uint16_t arraySize)
{
//    try
//    {
//        leftDirection = pt.get<int>("MovementFrameLeftRight.leftDirection");
//        rightDirection = pt.get<int>("MovementFrameLeftRight.rightDirection");
//        leftSidePWM = pt.get<int>("MovementFrameLeftRight.leftSidePWM");
//        rightSidePWM = pt.get<int>("MovementFrameLeftRight.rightSidePWM");
//        timeToDrive = pt.get<int>("MovementFrameLeftRight.timeToDrive");
//        shallQueue = pt.get<int>("MovementFrameLeftRight.shallQueue");

//    }
//    catch (const boost::exception& e)
//    {
//        std::string diag = diagnostic_information(e);
//        ROS_ERROR("Bad Movement frame received. Boost says: %s", diag.c_str());
//    }

    leftDirection = msgArray[0];
    rightDirection = msgArray[1];
    leftSidePWM = msgArray[2];
    rightSidePWM = msgArray[3];
    timeToDrive = msgArray[4];
    shallQueue = msgArray[5];
}

void Interface::DownstreamData::MovementOrderLeftRightFrame::doTheProcessing()
{

}
