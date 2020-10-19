#pragma once

#include "../DownstreamDataType.h"

namespace Interface
{
namespace DownstreamData

{
class MagnetometerFrame : public Interface::DownstreamDataType
{
private:

    int registryAddress;
    int registryValue;

public:

    MagnetometerFrame();
    virtual ~MagnetometerFrame();

    std::vector<uint8_t> serialize() override;
    void deserialize(const uint16_t *msgArray, uint16_t arraySize) override;
    void doTheProcessing() override;
};

}
}


