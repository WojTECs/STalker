#pragma once

#include "../DownstreamDataType.h"

namespace Interface
{
namespace DownstreamData
{

//This message type is used for SWORD and RAPTOR remotely controlled platforms and those that have separate turn and propulsion servo
class MovementFrameTurnPropulsion : public Interface::DownstreamDataType
{
private:

    int turnDirection;
    int propulsionDirection;

    int turnPWM;
    int propulsionPWM;

public:

    MovementFrameTurnPropulsion();
    virtual ~MovementFrameTurnPropulsion();

    std::vector<uint8_t> serialize();
    void deserialize(boost::property_tree::ptree& pt);
    void doTheProcessing();

};

}
}





