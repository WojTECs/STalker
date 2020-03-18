#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{

class TimeSyncFrame : public Interface::UpstreamDataType
{

private:

    uint32_t timeSync;

public:

    TimeSyncFrame();
    virtual ~TimeSyncFrame();

    void sendData(ROSInterface::ROSInterfaceClient& ROSClient) override;
    void deserialize(const char* iDataStream, const int iDataSize) override;
    std::string  serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}



