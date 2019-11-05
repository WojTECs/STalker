#pragma once

#include "../DownstreamDataType.h"

namespace Interface
{
namespace DownstreamData
{

//This message type is used for SWORD and RAPTOR remotely controlled platforms and those that have separate turn and propulsion servo
class MovementOrderTurnPropulsionFrame : public Interface::DownstreamDataType
{
private:

    uint8_t turnDirection;
    uint8_t propulsionDirection;

    uint16_t turnValue;
    uint16_t propulsionValue;

    uint32_t timeToDrive;
    uint8_t isQueued;

public:

    MovementOrderTurnPropulsionFrame();
    virtual ~MovementOrderTurnPropulsionFrame();

    std::vector<uint8_t> serialize();
    void deserialize(boost::property_tree::ptree& pt);
    void doTheProcessing();

};

}
}





