#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

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
        int16_t xAxis;
        int16_t yAxis;
        int16_t zAxis;
        int timestamp;
    };

    std::vector<Dataset> datasets;

public:

    MagnetometerFrame();
    virtual ~MagnetometerFrame();

    void deserialize(const char* iDataStream, const int iDataSize) override;
    std::string  serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}



