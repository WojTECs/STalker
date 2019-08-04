#include "TimerConfigurationFrame.h"


Interface::DatasToSend::TimerConfigurationFrame::TimerConfigurationFrame()
{
    mProtocolIndentificator = uint8_t{0x06};
}

Interface::DatasToSend::TimerConfigurationFrame::~TimerConfigurationFrame()
{

}
