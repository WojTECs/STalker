#include "MagnetometerFrame.h"

#include <ros/console.h>


Interface::UpstreamData::MagnetometerFrame::MagnetometerFrame()
{
    protocolIndentificator = uint8_t{0x06};
    datasetBinarySize = 10;
    rosTopic = "MagnetometerFrame";
}

Interface::UpstreamData::MagnetometerFrame::~MagnetometerFrame()
{

}

void Interface::UpstreamData::MagnetometerFrame::deserialize(std::vector<uint8_t> iDataStream)
{

    if(iDataStream.size() % datasetBinarySize != 0)
    {
        ROS_ERROR("Bad Magnetometer frame received. Length is mismatched");
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
