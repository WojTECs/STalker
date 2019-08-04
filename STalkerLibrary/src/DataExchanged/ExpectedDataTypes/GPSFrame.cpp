#include "GPSFrame.h"

Interface::ExpectedDataTypes::GPSFrame::GPSFrame()
{
  mProtocolIndentificator = uint8_t{0x08};
  mSTBinarySize = 20;//#TODO
}

Interface::ExpectedDataTypes::GPSFrame::~GPSFrame()
{

}

void Interface::ExpectedDataTypes::GPSFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

void Interface::ExpectedDataTypes::GPSFrame::doTheProcessing()
{

}
