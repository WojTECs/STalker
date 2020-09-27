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
    void deserialize(boost::property_tree::ptree& pt) override;
    void doTheProcessing() override;
};

}
}


