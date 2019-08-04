#include "GyroscopeFrame.h"

Interface::ExpectedDataTypes::GyroscopeFrame::GyroscopeFrame()
{
  mProtocolIndentificator = uint8_t{0x05};
  mSTBinarySize = 6;
}

Interface::ExpectedDataTypes::GyroscopeFrame::~GyroscopeFrame()
{

}

void Interface::ExpectedDataTypes::GyroscopeFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

void Interface::ExpectedDataTypes::GyroscopeFrame::doTheProcessing()
{

}
