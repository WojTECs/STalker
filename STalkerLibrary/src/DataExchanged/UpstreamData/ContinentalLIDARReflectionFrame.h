#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{

class ContinentalLIDARReflectionFrame : public Interface::UpstreamDataType
{

private:

    uint16_t leftBeamReflection;
    uint16_t centralBeamReflection;
    uint16_t rightBeamReflection;

public:

    ContinentalLIDARReflectionFrame();
    virtual ~ContinentalLIDARReflectionFrame();

    void sendData(ROSInterface::ROSInterfaceClient& ROSClient) override;
    void deserialize(const char* iDataStream, const int iDataSize) override;
    std::string  serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}



