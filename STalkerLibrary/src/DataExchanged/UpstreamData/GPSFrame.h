#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

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
    std::string  serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}



