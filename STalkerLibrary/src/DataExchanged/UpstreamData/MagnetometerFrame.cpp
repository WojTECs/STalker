#include "MagnetometerFrame.h"

#include <ros/console.h>


Interface::UpstreamData::MagnetometerFrame::MagnetometerFrame()
{
    protocolIndentificator = uint8_t{0x06};
    datasetBinarySize = 10;
    rosTopic = "MagnetometerFrame";
}

void Interface::UpstreamData::MagnetometerFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
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

Interface::UpstreamData::MagnetometerFrame::~MagnetometerFrame()
{

}

void Interface::UpstreamData::MagnetometerFrame::deserialize(const uint8_t *iDataStream, const int iDataSize)
{

    if(iDataSize % datasetBinarySize != 0)
    {
        ROS_ERROR("Bad Magnetometer frame received. Length is mismatched");
        return;
    }

    int dataCount = iDataSize / datasetBinarySize;

    datasets = std::vector<Dataset>(dataCount);


    int byteShift = 0;

    for (int i = 0; i < dataCount ;i++)
    {

        byteShift = i * datasetBinarySize;
        datasets[i].xAxis = int16_t((iDataStream[0 + byteShift]<<8) |
                (iDataStream[1 + byteShift] & 0xFF));

        datasets[i].yAxis = int16_t((iDataStream[2 + byteShift]<<8) |
                (iDataStream[3 + byteShift] & 0xFF));

        datasets[i].zAxis = int16_t((iDataStream[4 + byteShift]<<8) |
                (iDataStream[5 + byteShift] & 0xFF));

        datasets[i].timestamp = (iDataStream[6 + byteShift]<<24) |
                (iDataStream[7 + byteShift]<<16) |
                (iDataStream[8 + byteShift]<<8) |
                (iDataStream[9 + byteShift] & 0xFF);
    }
}

std::string Interface::UpstreamData::MagnetometerFrame::serialize()
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

    output.add_child("MagnetometerFrames", jsonDatasets);

    std::ostringstream pTreeToStringCatalizator;
    boost::property_tree::json_parser::write_json(pTreeToStringCatalizator, output);
    return pTreeToStringCatalizator.str();
}

void Interface::UpstreamData::MagnetometerFrame::doTheProcessing()
{
    for(int i = 0; i < datasets.size(); i++)
    {
        //tranforming on mG - miligauss using board xnucleo iks01a3
        //multipliers are derived from internal board settings for magnetometer with +-50G max range
        datasets[i].xAxis=datasets[i].xAxis * 1.5;
        datasets[i].yAxis=datasets[i].yAxis * 1.5;
        datasets[i].zAxis=datasets[i].zAxis * 1.5;
    }
}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::MagnetometerFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::MagnetometerFrame>magnetometerFrame(new Interface::UpstreamData::MagnetometerFrame);

    magnetometerFrame->protocolIndentificator = protocolIndentificator;
    magnetometerFrame->datasetBinarySize = datasetBinarySize;
    magnetometerFrame->rosTopic = rosTopic;

    return std::move(magnetometerFrame);

}
