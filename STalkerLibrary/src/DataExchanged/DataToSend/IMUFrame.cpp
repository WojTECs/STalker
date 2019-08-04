#include "IMUFrame.h"

Interface::DatasToSend::IMUFrame::IMUFrame()
{
    mProtocolIndentificator = uint8_t{0x08};
}

Interface::DatasToSend::IMUFrame::~IMUFrame()
{

}
