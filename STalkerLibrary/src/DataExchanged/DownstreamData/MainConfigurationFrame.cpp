#include "MainConfigurationFrame.h"

#include <boost/exception/diagnostic_information.hpp>
#include <ros/console.h>

Interface::DownstreamData::MainConfigurationFrame::MainConfigurationFrame()
{
    potocolIndentificator = "MainConfigurationFrame";
}

Interface::DownstreamData::MainConfigurationFrame::~MainConfigurationFrame()
{

}

std::vector<uint8_t> Interface::DownstreamData::MainConfigurationFrame::serialize()
{
    std::vector<uint8_t> output;

    output.push_back(0x00);//ID

    if(AccelerometerFrame)output.push_back(0x04);
    if(ContinentalLIDARDistanceFrame)output.push_back(0x0B);
    if(ContinentalLIDARReflectionFrame)output.push_back(0x0C);
    if(ContinentalLIDARSpeedFrame)output.push_back(0x0D);
    if(EncoderFrame)output.push_back(0x07);
    if(GPSFrame)output.push_back(0x08);
    if(GyroscopeFrame)output.push_back(0x05);
    if(LidarFrame)output.push_back(0x09);
    if(MagnetometerFrame)output.push_back(0x06);
    if(MovementInformationFrame)output.push_back(0x02);
    if(PackageStatisticsFrame)output.push_back(0xFE);
    if(RFIDFrame)output.push_back(0x0E);
    if(ServiceTimeFrame)output.push_back(0x11);
    if(TimersFrame)output.push_back(0x03);
    if(TimeSyncFrame)output.push_back(0xFF);

    return output;
}

void Interface::DownstreamData::MainConfigurationFrame::deserialize(boost::property_tree::ptree& pt)
{
    try
    {
        AccelerometerFrame = pt.get<int>("MainConfigurationFrame.AccelerometerFrame");
        ContinentalLIDARDistanceFrame = pt.get<int>("MainConfigurationFrame.ContinentalLIDARDistanceFrame");
        ContinentalLIDARReflectionFrame = pt.get<int>("MainConfigurationFrame.ContinentalLIDARReflectionFrame");
        ContinentalLIDARSpeedFrame = pt.get<int>("MainConfigurationFrame.ContinentalLIDARSpeedFrame");
        EncoderFrame = pt.get<int>("MainConfigurationFrame.EncoderFrame");
        GPSFrame = pt.get<int>("MainConfigurationFrame.GPSFrame");
        GyroscopeFrame = pt.get<int>("MainConfigurationFrame.GyroscopeFrame");
        LidarFrame = pt.get<int>("MainConfigurationFrame.LidarFrame");
        MagnetometerFrame = pt.get<int>("MainConfigurationFrame.MagnetometerFrame");
        MovementInformationFrame = pt.get<int>("MainConfigurationFrame.MovementInformationFrame");
        PackageStatisticsFrame = pt.get<int>("MainConfigurationFrame.PackageStatisticsFrame");
        RFIDFrame = pt.get<int>("MainConfigurationFrame.RFIDFrame");
        ServiceTimeFrame = pt.get<int>("MainConfigurationFrame.ServiceTimeFrame");
        TimersFrame = pt.get<int>("MainConfigurationFrame.TimersFrame");
        TimeSyncFrame = pt.get<int>("MainConfigurationFrame.TimeSyncFrame");
    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        ROS_ERROR("Bad Movement frame received. Boost says: %s", diag.c_str());
    }
}

void Interface::DownstreamData::MainConfigurationFrame::doTheProcessing()
{

}


