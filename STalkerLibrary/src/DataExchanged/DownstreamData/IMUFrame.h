#pragma once

#include "../DownstreamDataType.h"

namespace Interface
{
namespace DownstreamData

{
class IMUFrame : public Interface::DownstreamDataType
{
private:

    int registryAddress;
    int registryValue;

public:

    IMUFrame();
    virtual ~IMUFrame();

    std::vector<uint8_t> serialize() override;
    void deserialize(boost::property_tree::ptree& pt) override;
    void doTheProcessing() override;
};

}
}





