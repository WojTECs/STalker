#include "MagnetometerFrame.h"


STInterface::ExpectedDataTypes::MagnetometerFrame::MagnetometerFrame()
{
  mProtocolIndentificator = uint8_t{0x06};
  mSTBinarySize = 6;
}

STInterface::ExpectedDataTypes::MagnetometerFrame::~MagnetometerFrame()
{

}

void STInterface::ExpectedDataTypes::MagnetometerFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

void STInterface::ExpectedDataTypes::MagnetometerFrame::doTheProcessing()
{

}
