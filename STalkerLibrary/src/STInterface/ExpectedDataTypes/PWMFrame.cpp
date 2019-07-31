#include "PWMFrame.h"

STInterface::ExpectedDataTypes::PWMFrame::PWMFrame()
{
  mProtocolIndentificator = uint8_t{0x02};
  mSTBinarySize = 4;
}

STInterface::ExpectedDataTypes::PWMFrame::~PWMFrame()
{

}

void STInterface::ExpectedDataTypes::PWMFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

void STInterface::ExpectedDataTypes::PWMFrame::doTheProcessing()
{

}
