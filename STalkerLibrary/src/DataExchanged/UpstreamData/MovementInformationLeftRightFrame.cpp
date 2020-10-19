#include "MovementInformationLeftRightFrame.h"

#include <ros/console.h>

Interface::UpstreamData::MovementInformationLeftRightFrame::MovementInformationLeftRightFrame()
{
    protocolIndentificator = uint8_t{0x02};
    datasetBinarySize = 8;
    rosTopic = "MovementInformationFrame";
}

Interface::UpstreamData::MovementInformationLeftRightFrame::~MovementInformationLeftRightFrame()
{

}

void Interface::UpstreamData::MovementInformationLeftRightFrame::deserialize(const uint8_t *iDataStream, const int iDataSize)
{
    rightTurnDirection = (iDataStream[0] >> 4) & 0x0F;
    leftTurnDirection = iDataStream[0] & 0x0F;

    rightTurnValue = (iDataStream[1]<<8) | (iDataStream[2] & 0xFF);
    leftTurnValue = (iDataStream[3]<<8) | (iDataStream[4] & 0xFF);
    remainedTimeToDrive = (iDataStream[5]<<8) | (iDataStream[6] & 0xFF);
    howManyQueued = iDataStream[7];
}

std::string Interface::UpstreamData::MovementInformationLeftRightFrame::serialize()
{
    boost::property_tree::ptree output;
    boost::property_tree::ptree pwmData;

    pwmData.put("RightTurnDirection", rightTurnDirection);
    pwmData.put("LeftTurnDirection", leftTurnDirection);
    pwmData.put("RrightTurnValue", rightTurnValue);
    pwmData.put("LeftTurnValue", leftTurnValue);
    pwmData.put("RemainedTimeToDrive", remainedTimeToDrive);
    pwmData.put("QueueLength", howManyQueued);

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

void Interface::UpstreamData::MovementInformationLeftRightFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{

    std_msgs::UInt16MultiArray array;

    array.data.push_back(rightTurnDirection);
    array.data.push_back(leftTurnDirection);
    array.data.push_back(rightTurnValue);
    array.data.push_back(leftTurnValue);
    array.data.push_back(remainedTimeToDrive);
    array.data.push_back(howManyQueued);

    ROSClient.publishUInt16Array(array, rosTopic);
}
