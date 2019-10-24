#include "MovementFrameTurnPropulsion.h"

#include <boost/exception/diagnostic_information.hpp>
#include <ros/console.h>

Interface::DownstreamData::MovementFrameTurnPropulsion::MovementFrameTurnPropulsion()
{
    potocolIndentificator = "MovementFrameTurnPropulsion";
    stIdentifier = 0x04;
}

Interface::DownstreamData::MovementFrameTurnPropulsion::~MovementFrameTurnPropulsion()
{

}

std::vector<uint8_t> Interface::DownstreamData::MovementFrameTurnPropulsion::serialize()
{
    std::vector<uint8_t> output(6);

    output[0] = stIdentifier;
    output[1] = turnDirection << 4 || propulsionDirection;
    output[2] = turnPWM >> 8;
    output[3] = turnPWM & 0xFF;
    output[4] = propulsionPWM >> 8;
    output[5] = propulsionPWM % 256;

    return output;
}

void Interface::DownstreamData::MovementFrameTurnPropulsion::deserialize(boost::property_tree::ptree& pt)
{
    try
    {
        turnDirection = pt.get<int>("MovementFrameTurnPropulsion.turnDirection");
        propulsionDirection = pt.get<int>("MovementFrameTurnPropulsion.propulsionDirection");
        turnPWM = pt.get<int>("MovementFrameTurnPropulsion.turnPWM");
        propulsionPWM = pt.get<int>("MovementFrameTurnPropulsion.propulsionPWM");

    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        ROS_ERROR("Bad Movement frame received. Boost says: %s", diag.c_str());
    }
}

void Interface::DownstreamData::MovementFrameTurnPropulsion::doTheProcessing()
{

}

