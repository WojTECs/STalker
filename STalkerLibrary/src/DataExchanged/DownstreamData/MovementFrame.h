#pragma once

#include "../DownstreamDataType.h"

namespace Interface
{
namespace DownstreamData
{

class MovementFrame : public Interface::DownstreamDataType
{
private:

    int movementDirection;
    int leftSidePWM;
    int rightSidePWM;

public:

    MovementFrame();
    virtual ~MovementFrame();

    std::vector<uint8_t> serialize();
    void deserialize(boost::property_tree::ptree& pt);
    void doTheProcessing();

};

}
}





