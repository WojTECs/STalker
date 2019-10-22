#pragma once

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{
class TimersFrame : public Interface::UpstreamDataType
{
private:
public:

    TimersFrame();
    virtual ~TimersFrame();

    void deserialize(std::vector<uint8_t> iDataStream) override;
    boost::property_tree::ptree serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}


