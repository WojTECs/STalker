#include "IMUFrame.h"

STInterface::DatasToSend::IMUFrame::IMUFrame()
{
    mProtocolIndentificator = uint8_t{0x08};
}

STInterface::DatasToSend::IMUFrame::~IMUFrame()
{

}
