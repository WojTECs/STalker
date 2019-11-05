#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

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
    std::string serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}


