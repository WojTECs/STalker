#include "EncoderFrame.h"

Interface::ExpectedDataTypes::EncoderFrame::EncoderFrame()
{
  mProtocolIndentificator = uint8_t{0x07};
  mSTBinarySize = 4;
}

Interface::ExpectedDataTypes::EncoderFrame::~EncoderFrame()
{

}


void Interface::ExpectedDataTypes::EncoderFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

void Interface::ExpectedDataTypes::EncoderFrame::doTheProcessing()
{

}
