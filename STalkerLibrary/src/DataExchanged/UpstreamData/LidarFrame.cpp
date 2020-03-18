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

    std_msgs::Int32MultiArray array;

    array.data.push_back(distance);
    array.data.push_back(signalStrength);
    array.data.push_back(lidarMode);

    ROSClient.publishInt32Array(array, rosTopic);
}


void Interface::UpstreamData::LidarFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad Lidar frame received. Length is mismatching");
        return;
    }
    uint16_t distance = iDataStream[0]<<8 | iDataStream[1];
    uint16_t signalStrength = iDataStream[2]<<8 | iDataStream[3];
    uint8_t lidarMode = iDataStream[4];

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
