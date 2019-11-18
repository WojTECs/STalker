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

    void deserialize(const char* iDataStream, const int iDataSize) override;
    std::string serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}


