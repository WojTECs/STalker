#include "GyroscopeFrame.h"

#include <ros/console.h>

Interface::UpstreamData::GyroscopeFrame::GyroscopeFrame()
{
    protocolIndentificator = 0x05;
    datasetBinarySize = 10;
    rosTopic = "GyroscopeFrame";
}

void Interface::UpstreamData::GyroscopeFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{
    for(auto const& dataset: datasets)
    {
        std_msgs::Float64MultiArray array;
        array.data.push_back(dataset.xAxis);
        array.data.push_back(dataset.yAxis);
        array.data.push_back(dataset.zAxis);
        array.data.push_back(dataset.timestamp);

        ROSClient.publishFloat64Array(array, rosTopic);
    }
}

Interface::UpstreamData::GyroscopeFrame::~GyroscopeFrame()
{

}

void Interface::UpstreamData::GyroscopeFrame::deserialize(const char *iDataStream, const int iDataSize)
{

    if(iDataSize % datasetBinarySize != 0)
    {
        ROS_ERROR("Bad Gyroscope frame received. Lenght is mismatched");
        return;
    }

    int dataCount = iDataSize / datasetBinarySize;

    datasets = std::vector<Dataset>(dataCount);


    int byteShift = 0;

    for (int i = 0; i < dataCount ;i++)
    {

        byteShift = i * datasetBinarySize;
        datasets[i].xAxis = (iDataStream[0 + byteShift]<<8)+
                (iDataStream[1 + byteShift] & 0xFF);

        datasets[i].yAxis = (iDataStream[2 + byteShift]<<8)+
                (iDataStream[3 + byteShift] & 0xFF);

        datasets[i].zAxis = (iDataStream[4 + byteShift]<<8)+
                (iDataStream[5 + byteShift] & 0xFF);

        datasets[i].timestamp = (iDataStream[6 + byteShift]<<24)+
                (iDataStream[7 + byteShift]<<16)+
                (iDataStream[8 + byteShift]<<8)+
                (iDataStream[9 + byteShift] & 0xFF);
    }
}

std::string Interface::UpstreamData::GyroscopeFrame::serialize()
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

    output.add_child("GyroscopeFrames", jsonDatasets);

    std::ostringstream pTreeToStringCatalizator;
    boost::property_tree::json_parser::write_json(pTreeToStringCatalizator, output);
    return pTreeToStringCatalizator.str();
}

void Interface::UpstreamData::GyroscopeFrame::doTheProcessing()
{
    for(int i = 0; i < datasets.size(); i++)
    {
        //tranforming on mdps - milidegrees per second using board xnucleo iks01a3
        //multipliers are derived from internal board settings for gyroscope with 250dps max range
        datasets[i].xAxis=datasets[i].xAxis * 8.25;
        datasets[i].yAxis=datasets[i].yAxis * 8.25;
        datasets[i].zAxis=datasets[i].zAxis * 8.25;
    }
}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::GyroscopeFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::GyroscopeFrame>gyroscopeFrame(new Interface::UpstreamData::GyroscopeFrame);

    gyroscopeFrame->protocolIndentificator = protocolIndentificator;
    gyroscopeFrame->datasetBinarySize = datasetBinarySize;
    gyroscopeFrame->rosTopic = rosTopic;

    return std::move(gyroscopeFrame);

}
