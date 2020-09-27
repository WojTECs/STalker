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
    void deserialize(boost::property_tree::ptree& pt) override;
    void doTheProcessing() override;
};

}
}


