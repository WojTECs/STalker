#pragma once

#include <memory>

#include <boost/property_tree/ptree.hpp>


namespace Interface{

/// Translates data from JSON frames (ROS) format on the input (ST) binary format
class DownstreamDataType
{
private:
protected:
    std::string mProtocolIndentificator;

public:
    virtual ~DownstreamDataType(){}
    std::string getProtocolIdentificator() const{ return mProtocolIndentificator;}
    virtual  std::vector<uint8_t> serialize() = 0;
    virtual void deserialize(boost::property_tree::ptree& pt) = 0;
    virtual void doTheProcessing() = 0;
};

} //namespace STInterface
