#include "ContinentalLIDARDistanceFrame.h"

#include <ros/console.h>

Interface::UpstreamData::ContinentalLIDARDistanceFrame::ContinentalLIDARDistanceFrame()
{
    protocolIndentificator = uint8_t{0x0B};
    datasetBinarySize = 6;
    rosTopic = "ContinentalLIDARDistanceFrame";
}

Interface::UpstreamData::ContinentalLIDARDistanceFrame::~ContinentalLIDARDistanceFrame()
{

}

void Interface::UpstreamData::ContinentalLIDARDistanceFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{

    std_msgs::Float64MultiArray array;
    array.data.push_back(leftBeamDistance);
    array.data.push_back(centralBeamDistance);
    array.data.push_back(rightBeamDistance);

    ROSClient.publishFloat64Array(array, rosTopic);
}

void Interface::UpstreamData::ContinentalLIDARDistanceFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad Time Sync frame received. Length is mismatching");
        return;
    }

    leftBeamDistance = iDataStream[0]<<8 | iDataStream[1];
    centralBeamDistance = iDataStream[2]<<8 | iDataStream[3];
    rightBeamDistance = iDataStream[4]<<8 | iDataStream[5];
}

std::string Interface::UpstreamData::ContinentalLIDARDistanceFrame::serialize()
{

}

void Interface::UpstreamData::ContinentalLIDARDistanceFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::ContinentalLIDARDistanceFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::ContinentalLIDARDistanceFrame>continentalLIDARFrame(new Interface::UpstreamData::ContinentalLIDARDistanceFrame);

    continentalLIDARFrame->protocolIndentificator = protocolIndentificator;
    continentalLIDARFrame->datasetBinarySize = datasetBinarySize;
    continentalLIDARFrame->rosTopic = rosTopic;

    return std::move(continentalLIDARFrame);

}
