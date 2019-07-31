#include "MainConfigurationFrame.h"

STInterface::DatasToSend::MainConfigurationFrame::MainConfigurationFrame()
{
    mProtocolIndentificator = uint8_t{0x02};
}

STInterface::DatasToSend::MainConfigurationFrame::~MainConfigurationFrame()
{

}
