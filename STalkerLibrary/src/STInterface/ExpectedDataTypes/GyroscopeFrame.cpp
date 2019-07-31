#include "GyroscopeFrame.h"

STInterface::ExpectedDataTypes::GyroscopeFrame::GyroscopeFrame()
{
  mProtocolIndentificator = uint8_t{0x05};
  mSTBinarySize = 6;
}

STInterface::ExpectedDataTypes::GyroscopeFrame::~GyroscopeFrame()
{

}

void STInterface::ExpectedDataTypes::GyroscopeFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

void STInterface::ExpectedDataTypes::GyroscopeFrame::doTheProcessing()
{

}
