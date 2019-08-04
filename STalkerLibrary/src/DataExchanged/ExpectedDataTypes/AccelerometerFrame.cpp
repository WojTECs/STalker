#include "AccelerometerFrame.h"

Interface::ExpectedDataTypes::AccelerometerFrame::AccelerometerFrame()
{
    mProtocolIndentificator = uint8_t{0x04};
    mSTBinarySize = 6;
}

Interface::ExpectedDataTypes::AccelerometerFrame::~AccelerometerFrame()
{

}

void Interface::ExpectedDataTypes::AccelerometerFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

void Interface::ExpectedDataTypes::AccelerometerFrame::doTheProcessing()
{

}
