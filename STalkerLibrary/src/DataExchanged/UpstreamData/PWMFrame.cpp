#include "PWMFrame.h"

Interface::UpstreamData::PWMFrame::PWMFrame()
{
  protocolIndentificator = uint8_t{0x02};
  datasetBinarySize = 5;
}

Interface::UpstreamData::PWMFrame::~PWMFrame()
{

}

void Interface::UpstreamData::PWMFrame::deserialize(std::vector<uint8_t> iDataStream)
{
    //#TODO if DataStream != binsize log error
    try
    {
        movementDirection = iDataStream.at(0);
        leftSidePWM = (iDataStream.at(1)<<8)+iDataStream.at(2);
        rightSidePWM = (iDataStream.at(3)<<8)+iDataStream.at(4);
    }
    catch (const std::out_of_range& oor)
    {
        //#TODO handling and logging
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }
}

boost::property_tree::ptree Interface::UpstreamData::PWMFrame::serialize()
{
    boost::property_tree::ptree output;
    boost::property_tree::ptree pwmData;

    pwmData.put("MovementDirection", movementDirection ? "forward":"backward");
    pwmData.put("LeftSidePWM", leftSidePWM);
    pwmData.put("RightSidePWM", rightSidePWM);

    output.add_child("PWMFrame", pwmData);

    return output;
}

void Interface::UpstreamData::PWMFrame::doTheProcessing()
{

}
