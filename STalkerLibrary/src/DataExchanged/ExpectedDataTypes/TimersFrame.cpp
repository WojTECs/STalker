#include "TimersFrame.h"

Interface::ExpectedDataTypes::TimersFrame::TimersFrame()
{
  mProtocolIndentificator = uint8_t{0x03};
  mSTBinarySize = 0;//#TODO
}

Interface::ExpectedDataTypes::TimersFrame::~TimersFrame()
{

}

void Interface::ExpectedDataTypes::TimersFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

void Interface::ExpectedDataTypes::TimersFrame::doTheProcessing()
{

}

