#include "PackageStatisticsFrame.h"

#include <ros/console.h>

Interface::UpstreamData::PackageStatisticsFrame::PackageStatisticsFrame()
{
    protocolIndentificator = uint8_t{0xFE};
    datasetBinarySize = 8;
    rosTopic = "PackageStatisticsFrame";
}

Interface::UpstreamData::PackageStatisticsFrame::~PackageStatisticsFrame()
{

}

void Interface::UpstreamData::PackageStatisticsFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{

    std_msgs::Int32MultiArray array;

    array.data.push_back(sentPackages);
    array.data.push_back(malformedPackages);

    ROSClient.publishInt32Array(array, rosTopic);
}

void Interface::UpstreamData::PackageStatisticsFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize != datasetBinarySize)
    {
        ROS_ERROR("Bad Time Sync frame received. Length is mismatching");
        return;
    }
    sentPackages = iDataStream[0]<<24 | iDataStream[1]<<16 | iDataStream[2]<<8 | iDataStream[3];
    malformedPackages = iDataStream[4]<<24 | iDataStream[5]<<16 | iDataStream[6]<<8 | iDataStream[7];
}

std::string Interface::UpstreamData::PackageStatisticsFrame::serialize()
{

}

void Interface::UpstreamData::PackageStatisticsFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::PackageStatisticsFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::PackageStatisticsFrame>packageStatisticsFrame(new Interface::UpstreamData::PackageStatisticsFrame);

    packageStatisticsFrame->protocolIndentificator = protocolIndentificator;
    packageStatisticsFrame->datasetBinarySize = datasetBinarySize;
    packageStatisticsFrame->rosTopic = rosTopic;

    return std::move(packageStatisticsFrame);

}
