#pragma once

#include <memory>
#include <vector>

//#include <boost/property_tree/ptree.hpp>
#include <std_msgs/UInt16MultiArray.h>


namespace Interface{

/// Translates data from JSON frames (ROS) format on the input (ST) binary format
class DownstreamDataType
{
private:
protected:

    int stIdentifier;
    std::string potocolIndentificator;

public:

    virtual ~DownstreamDataType(){}
    int getProtocolIdentificator() const{ return stIdentifier;}
    virtual std::vector<uint8_t> serialize() = 0;
    virtual void deserialize(const uint16_t *msgArray, uint16_t arraySize) = 0;
    virtual void doTheProcessing() = 0;

};

} //namespace STInterface
