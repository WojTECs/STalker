#include "MovementInformationLeftRightFrame.h"

#include <ros/console.h>

Interface::UpstreamData::MovementInformationLeftRightFrame::MovementInformationLeftRightFrame()
{
    protocolIndentificator = uint8_t{0x02};
    datasetBinarySize = 7;
    rosTopic = "MovmentInformation";
}

Interface::UpstreamData::MovementInformationLeftRightFrame::~MovementInformationLeftRightFrame()
{

}

void Interface::UpstreamData::MovementInformationLeftRightFrame::deserialize(std::vector<uint8_t> iDataStream)
{
    if(iDataStream.size() != datasetBinarySize)
    {
        ROS_ERROR("Bad PWM frame received. Length is mismatched");
        return;
    }

    rightTurnDirection = iDataStream.at(0) >> 4;
    leftTurnDirection = iDataStream.at(0) & 0x0F;

    rightTurnValue = (iDataStream.at(1)<<8)+iDataStream.at(2);
    leftTurnValue = (iDataStream.at(3)<<8)+iDataStream.at(4);
    remainedTimeToDrive = (iDataStream.at(5)<<8)+iDataStream.at(6);
}

std::string Interface::UpstreamData::MovementInformationLeftRightFrame::serialize()
{
    boost::property_tree::ptree output;
    boost::property_tree::ptree pwmData;

    pwmData.put("RightTurnDirection", rightTurnDirection);
    pwmData.put("LeftTurnDirection", leftTurnDirection);
    pwmData.put("RrightTurnValue", rightTurnValue);
    pwmData.put("LeftTurnValue", leftTurnValue);
    pwmData.put("remainedTimeToDrive", remainedTimeToDrive);

    output.add_child("MovmentInformationFrame", pwmData);

    std::ostringstream pTreeToStringCatalizator;
    boost::property_tree::json_parser::write_json(pTreeToStringCatalizator, output);
    return pTreeToStringCatalizator.str();
}

void Interface::UpstreamData::MovementInformationLeftRightFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::MovementInformationLeftRightFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::MovementInformationLeftRightFrame>pwmFrame(new Interface::UpstreamData::MovementInformationLeftRightFrame);

    pwmFrame->protocolIndentificator = protocolIndentificator;
    pwmFrame->datasetBinarySize = datasetBinarySize;
    pwmFrame->rosTopic = rosTopic;

    return std::move(pwmFrame);

}
