#pragma once

#include <iostream>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <ros/console.h>

namespace Interface
{

// Translates data from input (ST) binary format on the JSON frames (ROS) format
class UpstreamDataType
{

private:
protected:

    uint8_t protocolIndentificator;
    std::size_t datasetBinarySize;

public:

    uint8_t getProtocolIdentificator() const{ return protocolIndentificator;}
    std::size_t getSTBinarySize() const{ return datasetBinarySize;}

    virtual void deserialize(std::vector<uint8_t> iDataStream)=0;
    virtual boost::property_tree::ptree serialize()=0;
    virtual void doTheProcessing()=0;

    virtual ~UpstreamDataType(){}
};

} //namespace STInterface
