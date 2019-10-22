#pragma once

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{
class MagnetometerFrame : public Interface::UpstreamDataType
{
private:

    struct Dataset
    {
        int xAxis;
        int yAxis;
        int zAxis;
        int timestamp;
    };

    std::vector<Dataset> datasets;

public:

    MagnetometerFrame();
    virtual ~MagnetometerFrame();

    void deserialize(std::vector<uint8_t> iDataStream) override;
    boost::property_tree::ptree serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}



