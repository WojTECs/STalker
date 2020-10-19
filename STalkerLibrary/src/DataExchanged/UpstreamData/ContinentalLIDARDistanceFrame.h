#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{

class ContinentalLIDARDistanceFrame : public Interface::UpstreamDataType
{

private:

    uint16_t leftBeamDistance;
    uint16_t centralBeamDistance;
    uint16_t rightBeamDistance;

public:

    ContinentalLIDARDistanceFrame();
    virtual ~ContinentalLIDARDistanceFrame();

    void sendData(ROSInterface::ROSInterfaceClient& ROSClient) override;
    void deserialize(const uint8_t* iDataStream, const int iDataSize) override;
    std::string  serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}



