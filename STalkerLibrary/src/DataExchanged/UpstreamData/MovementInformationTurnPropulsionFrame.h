#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{
class MovementInformationTurnPropulsionFrame : public Interface::UpstreamDataType
{
private:

    uint8_t turnDirection;
    uint8_t propulsionDirection;
    uint8_t howManyQueued;

    uint16_t turnValue;
    uint16_t propulsionValue;
    uint32_t remainedTimeToDrive;

public:

    MovementInformationTurnPropulsionFrame();
    virtual ~MovementInformationTurnPropulsionFrame();

    void deserialize(std::vector<uint8_t> iDataStream) override;
    std::string  serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}


