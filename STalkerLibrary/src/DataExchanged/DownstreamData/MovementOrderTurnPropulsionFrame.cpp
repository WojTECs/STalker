#include "MovementOrderTurnPropulsionFrame.h"

#include <boost/exception/diagnostic_information.hpp>
#include <ros/console.h>

Interface::DownstreamData::MovementOrderTurnPropulsionFrame::MovementOrderTurnPropulsionFrame()
{
    potocolIndentificator = "MovementFrameTurnPropulsion";
    stIdentifier = 0x02;
}

Interface::DownstreamData::MovementOrderTurnPropulsionFrame::~MovementOrderTurnPropulsionFrame()
{

}

std::vector<uint8_t> Interface::DownstreamData::MovementOrderTurnPropulsionFrame::serialize()
{
    std::vector<uint8_t> output(9);

    output[0] = stIdentifier;
    output[1] = turnDirection << 4 | propulsionDirection;
    output[2] = turnValue >> 8;
    output[3] = turnValue & 0xFF;
    output[4] = propulsionValue >> 8;
    output[5] = propulsionValue & 0xFF;
    output[6] = timeToDrive >> 8;
    output[7] = timeToDrive & 0xFF;
    output[8] = isQueued;

    return output;
}

void Interface::DownstreamData::MovementOrderTurnPropulsionFrame::deserialize(boost::property_tree::ptree& pt)
{
    try
    {
        turnDirection = pt.get<int>("MovementFrameTurnPropulsion.turnDirection");
        propulsionDirection = pt.get<int>("MovementFrameTurnPropulsion.propulsionDirection");
        turnValue = pt.get<int>("MovementFrameTurnPropulsion.turnValue");
        propulsionValue = pt.get<int>("MovementFrameTurnPropulsion.propulsionValue");
        timeToDrive = pt.get<int>("MovementFrameTurnPropulsion.timeToDrive");
        isQueued = pt.get<bool>("MovementFrameTurnPropulsion.isQueued");
    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        ROS_ERROR("Bad Movement frame received. Boost says: %s", diag.c_str());
    }
}

void Interface::DownstreamData::MovementOrderTurnPropulsionFrame::doTheProcessing()
{

}

