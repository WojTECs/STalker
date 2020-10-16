#include "ContinentalLIDARReflectionFrame.h"

#include <ros/console.h>

Interface::UpstreamData::ContinentalLIDARReflectionFrame::ContinentalLIDARReflectionFrame()
{
    protocolIndentificator = uint8_t{0x0C};
    datasetBinarySize = 6;
    rosTopic = "ContinentalLIDARReflectionFrame";
}

Interface::UpstreamData::ContinentalLIDARReflectionFrame::~ContinentalLIDARReflectionFrame()
{

}

void Interface::UpstreamData::ContinentalLIDARReflectionFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{

    std_msgs::UInt16MultiArray array;
    array.data.push_back(leftBeamReflection);
    array.data.push_back(centralBeamReflection);
    array.data.push_back(rightBeamReflection);

    ROSClient.publishUInt16Array(array, rosTopic);
}

void Interface::UpstreamData::ContinentalLIDARReflectionFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad Time Sync frame received. Length is mismatching");
        return;
    }

    leftBeamReflection = (iDataStream[0]<<8) | (iDataStream[1] & 0xFF);
    centralBeamReflection = (iDataStream[2]<<8) | (iDataStream[3] & 0xFF);
    rightBeamReflection = (iDataStream[4]<<8) | (iDataStream[5] & 0xFF);
}

std::string Interface::UpstreamData::ContinentalLIDARReflectionFrame::serialize()
{

}

void Interface::UpstreamData::ContinentalLIDARReflectionFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::ContinentalLIDARReflectionFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::ContinentalLIDARReflectionFrame>continentalLIDARFrame(new Interface::UpstreamData::ContinentalLIDARReflectionFrame);

    continentalLIDARFrame->protocolIndentificator = protocolIndentificator;
    continentalLIDARFrame->datasetBinarySize = datasetBinarySize;
    continentalLIDARFrame->rosTopic = rosTopic;

    return std::move(continentalLIDARFrame);

}
