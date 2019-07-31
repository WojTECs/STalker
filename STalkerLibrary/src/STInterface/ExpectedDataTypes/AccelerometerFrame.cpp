#include "AccelerometerFrame.h"

STInterface::ExpectedDataTypes::AccelerometerFrame::AccelerometerFrame()
{
    mProtocolIndentificator = uint8_t{0x04};
    mSTBinarySize = 6;
}

STInterface::ExpectedDataTypes::AccelerometerFrame::~AccelerometerFrame()
{

}

void STInterface::ExpectedDataTypes::AccelerometerFrame::deserialize(std::vector<uint8_t> iDataStream)
{

}

void STInterface::ExpectedDataTypes::AccelerometerFrame::doTheProcessing()
{

}
