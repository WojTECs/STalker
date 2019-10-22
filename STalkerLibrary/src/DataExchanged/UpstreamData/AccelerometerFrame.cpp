#include "AccelerometerFrame.h"

#include <ros/console.h>

Interface::UpstreamData::AccelerometerFrame::AccelerometerFrame()
{
    protocolIndentificator = uint8_t{0x04};
    datasetBinarySize = 10;
}

Interface::UpstreamData::AccelerometerFrame::~AccelerometerFrame()
{

}

void Interface::UpstreamData::AccelerometerFrame::deserialize(std::vector<uint8_t> iDataStream)
{
    if(iDataStream.size() % datasetBinarySize != 0)
    {
        ROS_ERROR("Bad Accelerometer frame received: wrong data lenght");
        return;
    }

    int dataCount = iDataStream.size() / datasetBinarySize;

    datasets = std::vector<Dataset>(dataCount);


    int byteShift = 0;

    for (int i = 0; i < dataCount ;i++)
    {

        byteShift = i * datasetBinarySize;
        datasets[i].xAxis = (iDataStream.at(0 + byteShift)<<8)+
                iDataStream.at(1 + byteShift);

        datasets[i].yAxis = (iDataStream.at(2 + byteShift)<<8)+
                iDataStream.at(3 + byteShift);

        datasets[i].zAxis = (iDataStream.at(4 + byteShift)<<8)+
                iDataStream.at(5 + byteShift);

        datasets[i].timestamp = (iDataStream.at(6 + byteShift)<<24)+
                (iDataStream.at(7 + byteShift)<<16)+
                (iDataStream.at(8 + byteShift)<<8)+
                iDataStream.at(9 + byteShift);
    }
}

boost::property_tree::ptree Interface::UpstreamData::AccelerometerFrame::serialize()
{
    boost::property_tree::ptree output;
    boost::property_tree::ptree jsonDatasets;
    boost::property_tree::ptree jsonDataset;

    for(auto const& dataset: datasets)
    {
        jsonDataset.put("xAxis", dataset.xAxis);
        jsonDataset.put("yAxis", dataset.yAxis);
        jsonDataset.put("zAxis", dataset.zAxis);
        jsonDataset.put("timestamp", dataset.timestamp);

        jsonDatasets.push_back(std::make_pair("", jsonDataset));
    }

    output.add_child("AccelerometerFrames", jsonDatasets);

    return output;
}

void Interface::UpstreamData::AccelerometerFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::AccelerometerFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::AccelerometerFrame>accelerometerFrame(new Interface::UpstreamData::AccelerometerFrame);
    return std::move(accelerometerFrame);
}
