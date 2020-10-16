#include "ServiceTimeFrame.h"

#include <ros/console.h>

Interface::UpstreamData::ServiceTimeFrame::ServiceTimeFrame()
{
    protocolIndentificator = uint8_t{0x11};
    datasetBinarySize = 12;
    rosTopic = "ServiceTimeFrame";
}

Interface::UpstreamData::ServiceTimeFrame::~ServiceTimeFrame()
{

}

void Interface::UpstreamData::ServiceTimeFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{

    std_msgs::UInt16MultiArray array;

    array.data.push_back(IMUTime);
    array.data.push_back(dataSendTime);
    array.data.push_back(EnkoderTime);
    array.data.push_back(PWMTime);
    array.data.push_back(LIDARTime);
    array.data.push_back(UltrasoundTime);

    ROSClient.publishUInt16Array(array, rosTopic);
}

void Interface::UpstreamData::ServiceTimeFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad Time Sync frame received. Length is mismatching");
        return;
    }

    IMUTime = (iDataStream[0]<<8) | (iDataStream[1] & 0xFF);
    dataSendTime = (iDataStream[2]<<8) | (iDataStream[3] & 0xFF);
    EnkoderTime = (iDataStream[4]<<8) | (iDataStream[5] & 0xFF);
    PWMTime = (iDataStream[6]<<8) | (iDataStream[7] & 0xFF);
    LIDARTime = (iDataStream[8]<<8) | (iDataStream[9] & 0xFF);
    UltrasoundTime = (iDataStream[10]<<8) | (iDataStream[11] & 0xFF);
}

std::string Interface::UpstreamData::ServiceTimeFrame::serialize()
{

}

void Interface::UpstreamData::ServiceTimeFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::ServiceTimeFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::ServiceTimeFrame> serviceTimeFrame(new Interface::UpstreamData::ServiceTimeFrame);

    serviceTimeFrame->protocolIndentificator = protocolIndentificator;
    serviceTimeFrame->datasetBinarySize = datasetBinarySize;
    serviceTimeFrame->rosTopic = rosTopic;

    return std::move(serviceTimeFrame);

}
