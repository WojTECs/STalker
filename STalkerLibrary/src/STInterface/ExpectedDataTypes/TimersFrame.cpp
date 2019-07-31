#include "TimersFrame.h"

STInterface::ExpectedDataTypes::TimersFrame::TimersFrame()
{
  mProtocolIndentificator = uint8_t{0x03};
  mSTBinarySize = 0;//#TODO
}

STInterface::ExpectedDataTypes::TimersFrame::~TimersFrame()
{

}

void STInterface::ExpectedDataTypes::TimersFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

void STInterface::ExpectedDataTypes::TimersFrame::doTheProcessing()
{

}

