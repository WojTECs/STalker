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

void Interface::UpstreamData::MovementInformationTurnPropulsionFrame::deserialize(std::vector<uint8_t> iDataStream)
{
    if(iDataStream.size() != datasetBinarySize)
    {
        ROS_ERROR("Bad PWM frame received. Length is mismatched");
        return;
    }

    turnDirection = iDataStream.at(0) >> 4;
    propulsionDirection = iDataStream.at(0) & 0x0F;

    turnValue = (iDataStream.at(1)<<8)+iDataStream.at(2);
    propulsionValue = (iDataStream.at(3)<<8)+iDataStream.at(4);
    remainedTimeToDrive = (iDataStream.at(5)<<8)+iDataStream.at(6);
    howManyQueued = iDataStream.at(7);
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
