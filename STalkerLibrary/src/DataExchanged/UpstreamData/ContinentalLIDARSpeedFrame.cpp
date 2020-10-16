#include "ContinentalLIDARSpeedFrame.h"

#include <ros/console.h>

Interface::UpstreamData::ContinentalLIDARSpeedFrame::ContinentalLIDARSpeedFrame()
{
    protocolIndentificator = uint8_t{0x0D};
    datasetBinarySize = 6;
    rosTopic = "ContinentalLIDARSpeedFrame";
}

Interface::UpstreamData::ContinentalLIDARSpeedFrame::~ContinentalLIDARSpeedFrame()
{

}

void Interface::UpstreamData::ContinentalLIDARSpeedFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{

    std_msgs::UInt16MultiArray array;
    array.data.push_back(leftBeamSpeed);
    array.data.push_back(centralBeamSpeed);
    array.data.push_back(rightBeamSpeed);

    ROSClient.publishUInt16Array(array, rosTopic);
}

void Interface::UpstreamData::ContinentalLIDARSpeedFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad Time Sync frame received. Length is mismatching");
        return;
    }

    leftBeamSpeed = (iDataStream[0]<<8) | (iDataStream[1] & 0xFF);
    centralBeamSpeed = (iDataStream[2]<<8) | (iDataStream[3] & 0xFF);
    rightBeamSpeed = (iDataStream[4]<<8) | (iDataStream[5] & 0xFF);
}

std::string Interface::UpstreamData::ContinentalLIDARSpeedFrame::serialize()
{

}

void Interface::UpstreamData::ContinentalLIDARSpeedFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::ContinentalLIDARSpeedFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::ContinentalLIDARSpeedFrame>continentalLIDARSpeedFrame(new Interface::UpstreamData::ContinentalLIDARSpeedFrame);

    continentalLIDARSpeedFrame->protocolIndentificator = protocolIndentificator;
    continentalLIDARSpeedFrame->datasetBinarySize = datasetBinarySize;
    continentalLIDARSpeedFrame->rosTopic = rosTopic;

    return std::move(continentalLIDARSpeedFrame);

}
