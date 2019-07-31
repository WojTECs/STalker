#include "TimerConfigurationFrame.h"


STInterface::DatasToSend::TimerConfigurationFrame::TimerConfigurationFrame()
{
    mProtocolIndentificator = uint8_t{0x06};
}

STInterface::DatasToSend::TimerConfigurationFrame::~TimerConfigurationFrame()
{

}
