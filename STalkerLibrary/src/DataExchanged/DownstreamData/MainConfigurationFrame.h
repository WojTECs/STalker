#pragma once

#include "../DownstreamDataType.h"

namespace Interface
{
namespace DownstreamData
{

class MainConfigurationFrame : public Interface::DownstreamDataType
{
private:

//    int AccelerometerFrame;
//    int ContinentalLIDARDistanceFrame;
//    int ContinentalLIDARReflectionFrame;
//    int ContinentalLIDARSpeedFrame;
//    int EncoderFrame;
//    int GPSFrame;
//    int GyroscopeFrame;
//    int LidarFrame;
//    int MagnetometerFrame;
//    int MovementInformationFrame;
//    int PackageStatisticsFrame;
//    int RFIDFrame;
//    int ServiceTimeFrame;
//    int TimersFrame;
//    int TimeSyncFrame;

    std::vector<uint8_t> dataset;
public:

    MainConfigurationFrame();
    virtual ~MainConfigurationFrame();

    std::vector<uint8_t> serialize();
    void deserialize(const uint16_t *msgArray, uint16_t arraySize);
    void doTheProcessing();

};
}
}





