#include "MagnetometerFrame.h"


Interface::UpstreamData::MagnetometerFrame::MagnetometerFrame()
{
  protocolIndentificator = uint8_t{0x06};
  datasetBinarySize = 10;
}

Interface::UpstreamData::MagnetometerFrame::~MagnetometerFrame()
{

}

void Interface::UpstreamData::MagnetometerFrame::deserialize(std::vector<uint8_t> iDataStream)
{
    //#TODO make it more beautiful
    if(iDataStream.size() % datasetBinarySize != 0)
    {
        //#TODO log error
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

boost::property_tree::ptree Interface::UpstreamData::MagnetometerFrame::serialize()
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

    return output;
}

void Interface::UpstreamData::MagnetometerFrame::doTheProcessing()
{

}
