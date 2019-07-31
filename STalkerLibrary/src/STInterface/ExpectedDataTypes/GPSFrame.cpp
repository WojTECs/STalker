#include "GPSFrame.h"

STInterface::ExpectedDataTypes::GPSFrame::GPSFrame()
{
  mProtocolIndentificator = uint8_t{0x08};
  mSTBinarySize = 20;//#TODO
}

STInterface::ExpectedDataTypes::GPSFrame::~GPSFrame()
{

}

void STInterface::ExpectedDataTypes::GPSFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

void STInterface::ExpectedDataTypes::GPSFrame::doTheProcessing()
{

}
