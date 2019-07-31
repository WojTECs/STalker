#include "MovementFrame.h"

STInterface::DatasToSend::MovementFrame::MovementFrame()
{
    mProtocolIndentificator = uint8_t{0x06};
}

STInterface::DatasToSend::MovementFrame::~MovementFrame()
{

}
