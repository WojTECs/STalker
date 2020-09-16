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

    std_msgs::Int32MultiArray array;

    array.data.push_back(IMUTime);
    array.data.push_back(dataSendTime);
    array.data.push_back(EnkoderTime);
    array.data.push_back(PWMTime);
    array.data.push_back(LIDARTime);
    array.data.push_back(UltrasoundTime);

    ROSClient.publishInt32Array(array, rosTopic);
}

void Interface::UpstreamData::ServiceTimeFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad Time Sync frame received. Length is mismatching");
        return;
    }

    IMUTime = (iDataStream[0]<<8)+iDataStream[2];
    dataSendTime= (iDataStream[1]<<8)+iDataStream[2];
    EnkoderTime= (iDataStream[1]<<8)+iDataStream[2];
    PWMTime= (iDataStream[1]<<8)+iDataStream[2];
    LIDARTime= (iDataStream[1]<<8)+iDataStream[2];
    UltrasoundTime= (iDataStream[1]<<8)+iDataStream[2];
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
