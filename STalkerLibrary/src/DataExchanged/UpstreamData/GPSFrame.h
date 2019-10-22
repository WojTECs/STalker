#pragma once

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{
class GPSFrame : public Interface::UpstreamDataType
{
private:
public:

    GPSFrame();
    virtual ~GPSFrame();

    void deserialize(std::vector<uint8_t> iDataStream) override;
    boost::property_tree::ptree serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}



