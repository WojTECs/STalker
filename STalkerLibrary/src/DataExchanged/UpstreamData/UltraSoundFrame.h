#pragma once

//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{


class UltraSoundFrame : public Interface::UpstreamDataType
{
private:
    uint16_t distance;

public:
    UltraSoundFrame();
    virtual ~UltraSoundFrame();

    void sendData(ROSInterface::ROSInterfaceClient& ROSClient) override;
    void deserialize(const uint8_t* iDataStream, const int iDataSize) override;
    std::string  serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}



