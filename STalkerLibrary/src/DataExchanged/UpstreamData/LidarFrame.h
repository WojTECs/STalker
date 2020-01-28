#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{


class LidarFrame : public Interface::UpstreamDataType
{
    union floatUnion {
        float value;
        uint8_t array[sizeof(float)];
    };
private:

    uint16_t distance;
    uint16_t signalStrength;
    uint8_t lidarMode;

public:

    LidarFrame();
    virtual ~LidarFrame();

    void deserialize(const char* iDataStream, const int iDataSize) override;
    std::string  serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}



