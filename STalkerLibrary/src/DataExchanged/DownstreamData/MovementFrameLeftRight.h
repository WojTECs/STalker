#pragma once

#include "../DownstreamDataType.h"

namespace Interface
{
namespace DownstreamData
{

//This message type is used for SWORD and RAPTOR remotely controlled platforms and those that have separate turn and propulsion servo
class MovementFrameLeftRight : public Interface::DownstreamDataType
{
private:

    int leftDirection;
    int rightDirection;

    int leftSidePWM;
    int rightSidePWM;

public:

    MovementFrameLeftRight();
    virtual ~MovementFrameLeftRight();

    std::vector<uint8_t> serialize();
    void deserialize(boost::property_tree::ptree& pt);
    void doTheProcessing();

};

}
}





