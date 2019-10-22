#include "PWMFrame.h"

#include <ros/console.h>

Interface::UpstreamData::PWMFrame::PWMFrame()
{
    protocolIndentificator = uint8_t{0x02};
    datasetBinarySize = 5;
}

Interface::UpstreamData::PWMFrame::~PWMFrame()
{

}

void Interface::UpstreamData::PWMFrame::deserialize(std::vector<uint8_t> iDataStream)
{
    if(iDataStream.size() != datasetBinarySize)
    {
        ROS_ERROR("Bad PWM frame received. Length is mismatched");
    }

    movementDirection = iDataStream.at(0);
    leftSidePWM = (iDataStream.at(1)<<8)+iDataStream.at(2);
    rightSidePWM = (iDataStream.at(3)<<8)+iDataStream.at(4);
}

boost::property_tree::ptree Interface::UpstreamData::PWMFrame::serialize()
{
    boost::property_tree::ptree output;
    boost::property_tree::ptree pwmData;

    pwmData.put("MovementDirection", movementDirection ? "forward":"backward");
    pwmData.put("LeftSidePWM", leftSidePWM);
    pwmData.put("RightSidePWM", rightSidePWM);

    output.add_child("PWMFrame", pwmData);

    return output;
}

void Interface::UpstreamData::PWMFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::PWMFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::PWMFrame>pwmFrame(new Interface::UpstreamData::PWMFrame);
    return std::move(pwmFrame);

}
