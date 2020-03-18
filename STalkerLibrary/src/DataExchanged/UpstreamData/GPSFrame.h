#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{
class GPSFrame : public Interface::UpstreamDataType
{
    union floatUnion
    {
        float value;
        uint8_t encoded[sizeof(float)];
    };
    
    union doubleUnion
    {
        double value;
        uint8_t encoded[sizeof(double)];
    };
private:
public:
    

    uint8_t countOfSatelites;
    floatUnion hdop;//precision coefficient
    doubleUnion latitude;// SI system decimal
    doubleUnion longitude;//SI system decimal
    floatUnion altitude; //SI system deciaml
    uint32_t infoAge;//data age
    uint8_t day;//date of reception
    uint8_t month;
    uint16_t year;
    
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    
    floatUnion course;//the angular difference in degrees from North
    floatUnion speed;//km/h
     
    
    GPSFrame();
    virtual ~GPSFrame();

    void sendData(ROSInterface::ROSInterfaceClient& ROSClient) override;
    void deserialize(const char* iDataStream, const int iDataSize) override;
    std::string  serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}



