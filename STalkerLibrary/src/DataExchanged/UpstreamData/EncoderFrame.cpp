#include "EncoderFrame.h"

#include <ros/console.h>

Interface::UpstreamData::EncoderFrame::EncoderFrame()
{
    protocolIndentificator = uint8_t{0x07};
    datasetBinarySize = 4;
}

Interface::UpstreamData::EncoderFrame::~EncoderFrame()
{

}


void Interface::UpstreamData::EncoderFrame::deserialize(std::vector<uint8_t> iDataStream)
{
    if(iDataStream.size() != datasetBinarySize)
    {
        ROS_ERROR("Bad Encoder frame received. Length is mismatching");
    }

    leftSideSpinCount = (iDataStream.at(0)<<8)+iDataStream.at(1);
    rightSideSpinCount = (iDataStream.at(2)<<8)+iDataStream.at(3);
}

boost::property_tree::ptree Interface::UpstreamData::EncoderFrame::serialize()
{
    boost::property_tree::ptree output;
    boost::property_tree::ptree pwmData;

    pwmData.put("LeftSideSpinCount", leftSideSpinCount);
    pwmData.put("RightSideSpinCount", rightSideSpinCount);

    output.add_child("EncoderFrame", pwmData);

    return output;
}

void Interface::UpstreamData::EncoderFrame::doTheProcessing()
{

}
