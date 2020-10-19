#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{
union floatUnion {
    float value;
    uint8_t array[sizeof(float)];
};

class EncoderFrame : public Interface::UpstreamDataType
{
private:

    uint8_t leftRotationDirection;
    uint8_t rightRotationDirection;
    
    floatUnion leftSideVelocity;
    floatUnion rightSideVelocity;
    
    floatUnion leftSideDistance;
    floatUnion rightSideDistance;

public:

    void sendData(ROSInterface::ROSInterfaceClient& ROSClient) override;

    EncoderFrame();
    virtual ~EncoderFrame();

    void deserialize(const uint8_t* iDataStream, const int iDataSize) override;
    std::string  serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}



