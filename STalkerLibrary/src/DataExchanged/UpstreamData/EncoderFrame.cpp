#include "EncoderFrame.h"

#include <ros/console.h>

Interface::UpstreamData::EncoderFrame::EncoderFrame()
{
    protocolIndentificator = uint8_t{0x07};
    datasetBinarySize = 17;
    rosTopic = "EncoderFrame";
}

Interface::UpstreamData::EncoderFrame::~EncoderFrame()
{

}


void Interface::UpstreamData::EncoderFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad Encoder frame received. Length is mismatching");
        return;
    }

    leftRotationDirection = (iDataStream[0]>>4);
    rightRotationDirection = (iDataStream[0]) & 0xF;

    leftSideVelocity.array[3] = iDataStream[1];
    leftSideVelocity.array[2] = iDataStream[2];
    leftSideVelocity.array[1] = iDataStream[3];
    leftSideVelocity.array[0] = iDataStream[4];

    leftSideDistance.array[3] = iDataStream[5];
    leftSideDistance.array[2] = iDataStream[6];
    leftSideDistance.array[1] = iDataStream[7];
    leftSideDistance.array[0] = iDataStream[8];

    rightSideVelocity.array[3] = iDataStream[9];
    rightSideVelocity.array[2] = iDataStream[10];
    rightSideVelocity.array[1] = iDataStream[11];
    rightSideVelocity.array[0] = iDataStream[12];

    rightSideDistance.array[3] = iDataStream[13];
    rightSideDistance.array[2] = iDataStream[14];
    rightSideDistance.array[1] = iDataStream[15];
    rightSideDistance.array[0] = iDataStream[16];

}

std::string Interface::UpstreamData::EncoderFrame::serialize()
{
    boost::property_tree::ptree output;
    boost::property_tree::ptree encoderData;

    encoderData.put("leftRotationDirection", leftRotationDirection);
    encoderData.put("rightRotationDirection", rightRotationDirection);
    encoderData.put("leftSideVelocity", leftSideVelocity.value);
    encoderData.put("rightSideVelocity", rightSideVelocity.value);
    encoderData.put("leftSideVelocity", leftSideVelocity.value);
    encoderData.put("rightSideVelocity", rightSideVelocity.value);

    output.add_child("EncoderFrame", encoderData);

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
