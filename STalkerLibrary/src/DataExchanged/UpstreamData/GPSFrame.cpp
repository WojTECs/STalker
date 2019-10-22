#include "GPSFrame.h"

#include <ros/console.h>

Interface::UpstreamData::GPSFrame::GPSFrame()
{
    protocolIndentificator = uint8_t{0x08};
    datasetBinarySize = 20;
}

Interface::UpstreamData::GPSFrame::~GPSFrame()
{

}

void Interface::UpstreamData::GPSFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

boost::property_tree::ptree Interface::UpstreamData::GPSFrame::serialize()
{

}

void Interface::UpstreamData::GPSFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::GPSFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::GPSFrame>gpsFrame(new Interface::UpstreamData::GPSFrame);
    return std::move(gpsFrame);

}
