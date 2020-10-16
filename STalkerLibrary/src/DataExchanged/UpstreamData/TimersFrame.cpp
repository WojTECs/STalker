#include "TimersFrame.h"

Interface::UpstreamData::TimersFrame::TimersFrame()
{
    protocolIndentificator = uint8_t{0x03};
    datasetBinarySize = 17;//Unknown yet therefore can't be implemented
    rosTopic = "TimersFrame";
}

Interface::UpstreamData::TimersFrame::~TimersFrame()
{

}

void Interface::UpstreamData::TimersFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    reg_psc_imu = (iDataStream[0]<<8) | (iDataStream[1] & 0xFF);
    reg_arr_imu = (iDataStream[2]<<8) | (iDataStream[3] & 0xFF);
    freq_imu = (iDataStream[4]<<24) | (iDataStream[5]<<16) | (iDataStream[6]<<8) | (iDataStream[7] & 0xFF);
    data_psc = (iDataStream[8]<<8) | (iDataStream[9] & 0xFF);
    data_arr = (iDataStream[10]<<8) | (iDataStream[11] & 0xFF);
    reg_clk_div_data_send = iDataStream[12] & 0xFF;
    freq_data_send = (iDataStream[13]<<24) | (iDataStream[14]<<16) | (iDataStream[15]<<8) | (iDataStream[16] & 0xFF);
}

std::string Interface::UpstreamData::TimersFrame::serialize()
{
//    boost::property_tree::ptree output;
//    boost::property_tree::ptree jsonDatasets;
//    boost::property_tree::ptree jsonDataset;

//    for(auto const& dataset: datasets)
//    {
//        jsonDataset.put("xAxis", dataset.xAxis);
//        jsonDataset.put("yAxis", dataset.yAxis);
//        jsonDataset.put("zAxis", dataset.zAxis);
//        jsonDataset.put("timestamp", dataset.timestamp);

//        jsonDatasets.push_back(std::make_pair("", jsonDataset));
//    }

//    output.add_child("GyroscopeFrames", jsonDatasets);

//    std::ostringstream pTreeToStringCatalizator;
//    boost::property_tree::json_parser::write_json(pTreeToStringCatalizator, output);
//    return pTreeToStringCatalizator.str();
}

void Interface::UpstreamData::TimersFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::TimersFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::TimersFrame>timersFrame(new Interface::UpstreamData::TimersFrame);


    timersFrame->protocolIndentificator = protocolIndentificator;
    timersFrame->datasetBinarySize = datasetBinarySize;
    timersFrame->rosTopic = rosTopic;

    return std::move(timersFrame);
}

void Interface::UpstreamData::TimersFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{
    std_msgs::UInt16MultiArray array;

    array.data.push_back(reg_psc_imu);
    array.data.push_back(reg_arr_imu);
    array.data.push_back(freq_imu);
    array.data.push_back(data_psc);
    array.data.push_back(data_arr);
    array.data.push_back(reg_clk_div_data_send);
    array.data.push_back(freq_data_send);

    ROSClient.publishUInt16Array(array, rosTopic);
}
