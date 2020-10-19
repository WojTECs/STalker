#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{

class ServiceTimeFrame : public Interface::UpstreamDataType
{

private:

    uint16_t IMUTime;
    uint16_t dataSendTime;
    uint16_t EnkoderTime;
    uint16_t PWMTime;
    uint16_t LIDARTime;
    uint16_t UltrasoundTime;


public:

    ServiceTimeFrame();
    virtual ~ServiceTimeFrame();

    void sendData(ROSInterface::ROSInterfaceClient& ROSClient) override;
    void deserialize(const uint8_t* iDataStream, const int iDataSize) override;
    std::string  serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}



