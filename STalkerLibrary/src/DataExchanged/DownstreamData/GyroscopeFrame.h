#pragma once

#include "../DownstreamDataType.h"

namespace Interface
{
namespace DownstreamData

{
class GyroscopeFrame : public Interface::DownstreamDataType
{
private:

    int registryAddress;
    int registryValue;

public:

    GyroscopeFrame();
    virtual ~GyroscopeFrame();

    std::vector<uint8_t> serialize() override;
    void deserialize(const uint16_t *msgArray, uint16_t arraySize) override;
    void doTheProcessing() override;
};

}
}


