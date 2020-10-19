#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{
class AccelerometerFrame : public Interface::UpstreamDataType
{
private:

    struct Dataset
    {
        float xAxis;
        float yAxis;
        float zAxis;
        uint32_t timestamp;
    };

    std::vector<Dataset> datasets;

public:

    void sendData(ROSInterface::ROSInterfaceClient& ROSClient) override;

    AccelerometerFrame();
    virtual ~AccelerometerFrame();

    void deserialize(const uint8_t* iDataStream, const int iDataSize) override;
    std::string serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}



