#pragma once

#include "../DownstreamDataType.h"

namespace Interface
{
namespace DownstreamData

{
class ElectromagnesFrame : public Interface::DownstreamDataType
{
private:

    int value;

public:

    ElectromagnesFrame();
    virtual ~ElectromagnesFrame();

    std::vector<uint8_t> serialize() override;
    void deserialize(const uint16_t *msgArray, uint16_t arraySize) override;
    void doTheProcessing() override;
};

}
}


