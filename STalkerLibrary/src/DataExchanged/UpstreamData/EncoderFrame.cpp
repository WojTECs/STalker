#include "EncoderFrame.h"

#include <ros/console.h>

Interface::UpstreamData::EncoderFrame::EncoderFrame()
{
    protocolIndentificator = uint8_t{0x07};
    datasetBinarySize = 4;
    rosTopic = "EncoderFrame";
}

Interface::UpstreamData::EncoderFrame::~EncoderFrame()
{

}


void Interface::UpstreamData::EncoderFrame::deserialize(std::vector<uint8_t> iDataStream)
{
    if(iDataStream.size() != datasetBinarySize)
    {
        ROS_ERROR("Bad Encoder frame received. Length is mismatching");
        return;
    }

    leftSideSpinCount = (iDataStream.at(0)<<8)+iDataStream.at(1);
    rightSideSpinCount = (iDataStream.at(2)<<8)+iDataStream.at(3);
}

std::string Interface::UpstreamData::EncoderFrame::serialize()
{
    boost::property_tree::ptree output;
    boost::property_tree::ptree pwmData;

    pwmData.put("LeftSideSpinCount", leftSideSpinCount);
    pwmData.put("RightSideSpinCount", rightSideSpinCount);

    output.add_child("EncoderFrame", pwmData);

    std::ostringstream pTreeToStringCatalizator;
    boost::property_tree::json_parser::write_json(pTreeToStringCatalizator, output);
    return pTreeToStringCatalizator.str();
}

void Interface::UpstreamData::EncoderFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::EncoderFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::EncoderFrame>encoderFrame(new Interface::UpstreamData::EncoderFrame);

    encoderFrame->protocolIndentificator = protocolIndentificator;
    encoderFrame->datasetBinarySize = datasetBinarySize;
    encoderFrame->rosTopic = rosTopic;

    return std::move(encoderFrame);

}
