#pragma once

#include <iostream>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <ros/console.h>

#include <ros/console.h>

#include "../ROSInterface/ROSInterfaceClient.h"


namespace ROSInterface
{
    class ROSInterfaceClient;
}

namespace Interface
{

// Translates data from input (ST) binary format on the JSON frames (ROS) format
class UpstreamDataType
{

private:
protected:

    uint8_t protocolIndentificator;
    std::size_t datasetBinarySize;
    std::string rosTopic;

public:

    uint8_t getProtocolIdentificator() const{ return protocolIndentificator;}
    std::size_t getSTBinarySize() const{ return datasetBinarySize;}

    std::string getRosTopic()const{ return rosTopic;}
    void setRosTopic(std::string topic){rosTopic=topic;}

    virtual void sendData(ROSInterface::ROSInterfaceClient& ROSClient);

    virtual void deserialize(const char* iDataStream, const int iDataSize)=0;
    virtual std::string serialize()=0;
    virtual void doTheProcessing()=0;

    virtual std::unique_ptr<Interface::UpstreamDataType> getClone()=0;

    virtual ~UpstreamDataType(){}
};

} //namespace STInterface
