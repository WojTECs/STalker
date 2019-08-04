#include "PWMFrame.h"

Interface::ExpectedDataTypes::PWMFrame::PWMFrame()
{
  mProtocolIndentificator = uint8_t{0x02};
  mSTBinarySize = 4;
}

Interface::ExpectedDataTypes::PWMFrame::~PWMFrame()
{

}

void Interface::ExpectedDataTypes::PWMFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

void Interface::ExpectedDataTypes::PWMFrame::doTheProcessing()
{

}
