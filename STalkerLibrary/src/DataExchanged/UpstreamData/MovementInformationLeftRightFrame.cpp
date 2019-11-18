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

void Interface::UpstreamData::MovementInformationLeftRightFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad PWM frame received. Length is mismatched");
        return;
    }

    rightTurnDirection = iDataStream[0] >> 4;
    leftTurnDirection = iDataStream[0] & 0x0F;

    rightTurnValue = (iDataStream[1]<<8)+iDataStream[2];
    leftTurnValue = (iDataStream[3]<<8)+iDataStream[4];
    remainedTimeToDrive = (iDataStream[5]<<8)+iDataStream[6];
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
