#pragma once

#include "../DownstreamDataType.h"

namespace Interface
{
namespace DownstreamData

{
class AccelerometerFrame : public Interface::DownstreamDataType
{
private:

    int registryAddress;
    int registryValue;

public:

    AccelerometerFrame();
    virtual ~AccelerometerFrame();

    std::vector<uint8_t> serialize() override;
    void deserialize(const uint16_t *msgArray, uint16_t arraySize) override;
    void doTheProcessing() override;
};

}
}


