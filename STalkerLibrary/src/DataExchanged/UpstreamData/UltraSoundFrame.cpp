#include "UltraSoundFrame.h"

#include <ros/console.h>

Interface::UpstreamData::UltraSoundFrame::UltraSoundFrame()
{
    protocolIndentificator = uint8_t{0x0F};
    datasetBinarySize = 2;
    rosTopic = "UltraSoundFrame";
}

Interface::UpstreamData::UltraSoundFrame::~UltraSoundFrame()
{

}

void Interface::UpstreamData::UltraSoundFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{
    std_msgs::UInt16 uSound;

    uSound.data = distance;

    ROSClient.publishUInt16(uSound, rosTopic);
}

void Interface::UpstreamData::UltraSoundFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad UltraSound frame received. Length is mismatching");
        return;
    }
    distance = (iDataStream[0]<<8) | (iDataStream[1] & 0xFF);
}

std::string Interface::UpstreamData::UltraSoundFrame::serialize()
{

}

void Interface::UpstreamData::UltraSoundFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::UltraSoundFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::UltraSoundFrame>ultraSoundFrame(new Interface::UpstreamData::UltraSoundFrame);

    ultraSoundFrame->protocolIndentificator = protocolIndentificator;
    ultraSoundFrame->datasetBinarySize = datasetBinarySize;
    ultraSoundFrame->rosTopic = rosTopic;

    return std::move(ultraSoundFrame);
}
