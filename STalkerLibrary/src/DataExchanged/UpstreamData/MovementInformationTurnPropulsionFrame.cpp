#include "MovementInformationTurnPropulsionFrame.h"

#include <ros/console.h>

Interface::UpstreamData::MovementInformationTurnPropulsionFrame::MovementInformationTurnPropulsionFrame()
{
    protocolIndentificator = uint8_t{0x02};
    datasetBinarySize = 8;
    rosTopic = "MovmentInformationFrame";
}

Interface::UpstreamData::MovementInformationTurnPropulsionFrame::~MovementInformationTurnPropulsionFrame()
{

}

void Interface::UpstreamData::MovementInformationTurnPropulsionFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{

    std_msgs::Int32MultiArray array;

    array.data.push_back(turnDirection);
    array.data.push_back(propulsionDirection);
    array.data.push_back(turnValue);
    array.data.push_back(propulsionValue);
    array.data.push_back(remainedTimeToDrive);
    array.data.push_back(howManyQueued);

    ROSClient.publishInt32Array(array, rosTopic);
}

void Interface::UpstreamData::MovementInformationTurnPropulsionFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad PWM frame received. Length is mismatched");
        return;
    }

    turnDirection = iDataStream[0] >> 4;
    propulsionDirection = iDataStream[0] & 0x0F;

    turnValue = (iDataStream[1]<<8)+iDataStream[2];
    propulsionValue = (iDataStream[3]<<8)+iDataStream[4];
    remainedTimeToDrive = (iDataStream[5]<<8)+iDataStream[6];
    howManyQueued = iDataStream[7];
}

std::string Interface::UpstreamData::MovementInformationTurnPropulsionFrame::serialize()
{
    boost::property_tree::ptree output;
    boost::property_tree::ptree pwmData;

    pwmData.put("TurnDirection", turnDirection);
    pwmData.put("PropulsionDirection", propulsionDirection);
    pwmData.put("TurnValue", turnValue);
    pwmData.put("PropulsionValue", propulsionValue);
    pwmData.put("RemainedTimeToDrive", remainedTimeToDrive);
    pwmData.put("HowManyQueued", howManyQueued);

    output.add_child("MovmentInformationFrame", pwmData);

    std::ostringstream pTreeToStringCatalizator;
    boost::property_tree::json_parser::write_json(pTreeToStringCatalizator, output);
    return pTreeToStringCatalizator.str();
}

void Interface::UpstreamData::MovementInformationTurnPropulsionFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::MovementInformationTurnPropulsionFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::MovementInformationTurnPropulsionFrame>pwmFrame(new Interface::UpstreamData::MovementInformationTurnPropulsionFrame);

    pwmFrame->protocolIndentificator = protocolIndentificator;
    pwmFrame->datasetBinarySize = datasetBinarySize;
    pwmFrame->rosTopic = rosTopic;

    return std::move(pwmFrame);

}
