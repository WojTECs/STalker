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
    void deserialize(boost::property_tree::ptree& pt) override;
    void doTheProcessing() override;
};

}
}


