#pragma once

#include "../DownstreamDataType.h"

namespace Interface
{
namespace DownstreamData
{

class TimerConfigurationFrame : public Interface::DownstreamDataType
{
private:

    int timerID;
    int prescalerValue;
    int counterValue;
    int clockDivider;

public:

    TimerConfigurationFrame();
    virtual ~TimerConfigurationFrame();

    std::vector<uint8_t> serialize();
    void deserialize(const uint16_t *msgArray, uint16_t arraySize);
    void doTheProcessing();

};
}
}




