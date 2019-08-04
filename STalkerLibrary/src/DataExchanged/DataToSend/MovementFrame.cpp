#include "MovementFrame.h"

Interface::DatasToSend::MovementFrame::MovementFrame()
{
    mProtocolIndentificator = uint8_t{0x06};
}

Interface::DatasToSend::MovementFrame::~MovementFrame()
{

}
