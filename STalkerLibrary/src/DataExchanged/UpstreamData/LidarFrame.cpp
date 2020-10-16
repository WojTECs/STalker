#include "LidarFrame.h"

#include <ros/console.h>

Interface::UpstreamData::LidarFrame::LidarFrame()
{
    protocolIndentificator = uint8_t{0x09};
    datasetBinarySize = 5;
    rosTopic = "LidarFrame";
}

Interface::UpstreamData::LidarFrame::~LidarFrame()
{

}

void Interface::UpstreamData::LidarFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{
    std_msgs::UInt16MultiArray array;

    array.data.push_back(distance);
    array.data.push_back(signalStrength);
    array.data.push_back(lidarMode);

    ROSClient.publishUInt16Array(array, rosTopic);

    sensor_msgs::LaserScan lscan;

    lscan.angle_min = M_PI_2;
    lscan.angle_max = M_PI_2;
    lscan.angle_increment = 0;
    lscan.time_increment = 0;
    lscan.scan_time = 0;
    lscan.range_min = 0.03;
    lscan.range_max = 12;
    lscan.ranges.push_back(distance / 100); // cm -> m
    lscan.intensities.push_back(signalStrength);

    ROSClient.publishLaserScan(lscan, rosTopic + "Scan");
}

void Interface::UpstreamData::LidarFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad Lidar frame received. Length is mismatching");
        return;
    }
    distance = (iDataStream[0]<<8) | (iDataStream[1] & 0xFF);
    signalStrength = (iDataStream[2]<<8) | (iDataStream[3] & 0xFF);
    lidarMode = iDataStream[4];

}

std::string Interface::UpstreamData::LidarFrame::serialize()
{
    boost::property_tree::ptree output;
    boost::property_tree::ptree lidarData;

    lidarData.put("distance", distance);
    lidarData.put("signalStrength", signalStrength);
    lidarData.put("lidarMode", lidarMode);

    output.add_child("LidarFrame", lidarData);

    std::ostringstream pTreeToStringCatalizator;
    boost::property_tree::json_parser::write_json(pTreeToStringCatalizator, output);
    return pTreeToStringCatalizator.str();
}

void Interface::UpstreamData::LidarFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::LidarFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::LidarFrame>lidarFrame(new Interface::UpstreamData::LidarFrame);

    lidarFrame->protocolIndentificator = protocolIndentificator;
    lidarFrame->datasetBinarySize = datasetBinarySize;
    lidarFrame->rosTopic = rosTopic;

    return std::move(lidarFrame);

}
