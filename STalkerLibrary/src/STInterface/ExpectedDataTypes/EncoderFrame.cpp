#include "EncoderFrame.h"

STInterface::ExpectedDataTypes::EncoderFrame::EncoderFrame()
{
  mProtocolIndentificator = uint8_t{0x07};
  mSTBinarySize = 4;
}

STInterface::ExpectedDataTypes::EncoderFrame::~EncoderFrame()
{

}


void STInterface::ExpectedDataTypes::EncoderFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

void STInterface::ExpectedDataTypes::EncoderFrame::doTheProcessing()
{

}
