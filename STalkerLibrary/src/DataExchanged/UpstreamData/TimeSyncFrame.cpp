#include "TimeSyncFrame.h"

#include <ros/console.h>

Interface::UpstreamData::TimeSyncFrame::TimeSyncFrame()
{
    protocolIndentificator = uint8_t{0xFF};
    datasetBinarySize = 4;
    rosTopic = "TimeSyncFrame";
}

Interface::UpstreamData::TimeSyncFrame::~TimeSyncFrame()
{

}

void Interface::UpstreamData::TimeSyncFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{

    std_msgs::UInt32 data;

    data.data = timeSync;

    ROSClient.publishUInt32(data, rosTopic);
}

void Interface::UpstreamData::TimeSyncFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad Time Sync frame received. Length is mismatching");
        return;
    }
    timeSync = iDataStream[0]<<24 | iDataStream[1]<<16 | iDataStream[2]<<8 | iDataStream[3];
}

std::string Interface::UpstreamData::TimeSyncFrame::serialize()
{
    boost::property_tree::ptree output;
    boost::property_tree::ptree timeSyncData;

    timeSyncData.put("timeSync", timeSync);

    output.add_child("EncoderFrame", timeSyncData);

    std::ostringstream pTreeToStringCatalizator;
    boost::property_tree::json_parser::write_json(pTreeToStringCatalizator, output);
    return pTreeToStringCatalizator.str();
}

void Interface::UpstreamData::TimeSyncFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::TimeSyncFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::TimeSyncFrame>timeSyncFrame(new Interface::UpstreamData::TimeSyncFrame);

    timeSyncFrame->protocolIndentificator = protocolIndentificator;
    timeSyncFrame->datasetBinarySize = datasetBinarySize;
    timeSyncFrame->rosTopic = rosTopic;

    return std::move(timeSyncFrame);

}
