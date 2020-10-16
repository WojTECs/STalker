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

    std_msgs::UInt16MultiArray array;
    array.data.push_back(leftBeamDistance);
    array.data.push_back(centralBeamDistance);
    array.data.push_back(rightBeamDistance);

    ROSClient.publishUInt16Array(array, rosTopic);

    sensor_msgs::LaserScan lscan;
    lscan.angle_min = M_PI_2 - 0.16; //0.16 rad -> 9 deg.
    lscan.angle_max = M_PI_2 + 0.16;
    lscan.angle_increment = 0.16;
    lscan.time_increment = 0;
    lscan.scan_time = 0;
    lscan.range_min = 1;
    lscan.range_max = 13.5;
    lscan.ranges.push_back(leftBeamDistance / 100);
    lscan.ranges.push_back(centralBeamDistance / 100);
    lscan.ranges.push_back(rightBeamDistance / 100);

    ROSClient.publishLaserScan(lscan, rosTopic + "Scan");
}

void Interface::UpstreamData::ContinentalLIDARDistanceFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad Time Sync frame received. Length is mismatching");
        return;
    }

    leftBeamDistance = (iDataStream[0]<<8) | (iDataStream[1] & 0xFF);
    centralBeamDistance = (iDataStream[2]<<8) | (iDataStream[3] & 0xFF);
    rightBeamDistance = (iDataStream[4]<<8) | (iDataStream[5] & 0xFF);
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
