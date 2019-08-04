#include "MagnetometerFrame.h"


Interface::ExpectedDataTypes::MagnetometerFrame::MagnetometerFrame()
{
  mProtocolIndentificator = uint8_t{0x06};
  mSTBinarySize = 6;
}

Interface::ExpectedDataTypes::MagnetometerFrame::~MagnetometerFrame()
{

}

void Interface::ExpectedDataTypes::MagnetometerFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

void Interface::ExpectedDataTypes::MagnetometerFrame::doTheProcessing()
{

}
