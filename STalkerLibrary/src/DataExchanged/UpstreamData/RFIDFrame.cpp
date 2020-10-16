#include "RFIDFrame.h"

#include <ros/console.h>

Interface::UpstreamData::RFIDFrame::RFIDFrame()
{
    protocolIndentificator = uint8_t{0x0E};
    datasetBinarySize = 5;
    rosTopic = "RFIDFrame";
}

Interface::UpstreamData::RFIDFrame::~RFIDFrame()
{

}

void Interface::UpstreamData::RFIDFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{

    std_msgs::UInt8MultiArray array;

    array.data.push_back(cardID[0]);
    array.data.push_back(cardID[1]);
    array.data.push_back(cardID[2]);
    array.data.push_back(cardID[3]);
    array.data.push_back(cardID[4]);

    ROSClient.publishUInt8Array(array, rosTopic);
}

void Interface::UpstreamData::RFIDFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad Time Sync frame received. Length is mismatching");
        return;
    }

    cardID[0] = iDataStream[0];
    cardID[1] = iDataStream[1];
    cardID[2] = iDataStream[2];
    cardID[3] = iDataStream[3];
    cardID[4] = iDataStream[4];
}

std::string Interface::UpstreamData::RFIDFrame::serialize()
{

}

void Interface::UpstreamData::RFIDFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::RFIDFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::RFIDFrame>frame(new Interface::UpstreamData::RFIDFrame);

    frame->protocolIndentificator = protocolIndentificator;
    frame->datasetBinarySize = datasetBinarySize;
    frame->rosTopic = rosTopic;

    return std::move(frame);

}
