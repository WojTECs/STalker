#include <memory>

#include "STalkerLibraryInterface.h"

int main(int argc, char **argv)
{

    ros::init(argc, argv, "STalker");
    ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug);

    std::shared_ptr<ROSInterface::ROSInterfaceClient> rosClient;
    std::shared_ptr<STInterface::STInterfaceClientUDP> stClient;

    try
    {
        stClient = std::make_shared<STInterface::STInterfaceClientUDP>(1115, "192.168.1.10", "7");
    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        ROS_FATAL("Exception received during STInterface creation: %s", diag.c_str());
        return 0;
    }

    try
    {
        rosClient = std::make_shared<ROSInterface::ROSInterfaceClient>();
    }
    catch (const std::exception e)
    {

        ROS_FATAL("Exception received during ROSInterface creation");
        return 0;
    }

    stClient->setROSInterface(rosClient);
    rosClient->setSTUDPInterface(stClient);

    std::unique_ptr<Interface::DownstreamData::AccelerometerFrame> aFrame(new Interface::DownstreamData::AccelerometerFrame);
    rosClient->addExpectedDataType(std::move(aFrame));
    std::unique_ptr<Interface::DownstreamData::ElectromagnesFrame> eFrame(new Interface::DownstreamData::ElectromagnesFrame);
    rosClient->addExpectedDataType(std::move(eFrame));
    std::unique_ptr<Interface::DownstreamData::GyroscopeFrame> gFrame(new Interface::DownstreamData::GyroscopeFrame);
    rosClient->addExpectedDataType(std::move(gFrame));
    std::unique_ptr<Interface::DownstreamData::MagnetometerFrame> mFrame(new Interface::DownstreamData::MagnetometerFrame);
    rosClient->addExpectedDataType(std::move(mFrame));
    std::unique_ptr<Interface::DownstreamData::MainConfigurationFrame> cFrame(new Interface::DownstreamData::MainConfigurationFrame);
    rosClient->addExpectedDataType(std::move(cFrame));
    std::unique_ptr<Interface::DownstreamData::MovementOrderLeftRightFrame> movementFrame(new Interface::DownstreamData::MovementOrderLeftRightFrame);
    rosClient->addExpectedDataType(std::move(movementFrame));
    std::unique_ptr<Interface::DownstreamData::TimerConfigurationFrame> timerConfigurationFrame(new Interface::DownstreamData::TimerConfigurationFrame);
    rosClient->addExpectedDataType(std::move(timerConfigurationFrame));

    std::unique_ptr<Interface::UpstreamData::AccelerometerFrame>accelerometerFrame(new Interface::UpstreamData::AccelerometerFrame);
    stClient->addExpectedDataType(std::move(accelerometerFrame));
    std::unique_ptr<Interface::UpstreamData::ContinentalLIDARDistanceFrame>continentalLIDARDistanceFrame(new Interface::UpstreamData::ContinentalLIDARDistanceFrame);
    stClient->addExpectedDataType(std::move(continentalLIDARDistanceFrame));
    std::unique_ptr<Interface::UpstreamData::ContinentalLIDARReflectionFrame>continentalLIDARReflectionFrame(new Interface::UpstreamData::ContinentalLIDARReflectionFrame);
    stClient->addExpectedDataType(std::move(continentalLIDARReflectionFrame));
    std::unique_ptr<Interface::UpstreamData::ContinentalLIDARSpeedFrame>continentalLIDARSpeedFrame(new Interface::UpstreamData::ContinentalLIDARSpeedFrame);
    stClient->addExpectedDataType(std::move(continentalLIDARSpeedFrame));
    std::unique_ptr<Interface::UpstreamData::EncoderFrame>encoderFrame(new Interface::UpstreamData::EncoderFrame);
    stClient->addExpectedDataType(std::move(encoderFrame));
    std::unique_ptr<Interface::UpstreamData::GPSFrame>gpsFrame(new Interface::UpstreamData::GPSFrame);
    stClient->addExpectedDataType(std::move(gpsFrame));
    std::unique_ptr<Interface::UpstreamData::GyroscopeFrame>gyroscopeFrame(new Interface::UpstreamData::GyroscopeFrame);
    stClient->addExpectedDataType(std::move(gyroscopeFrame));
    std::unique_ptr<Interface::UpstreamData::LidarFrame>lidarFrame(new Interface::UpstreamData::LidarFrame);
    stClient->addExpectedDataType(std::move(lidarFrame));
    std::unique_ptr<Interface::UpstreamData::MagnetometerFrame>magnetometerFrame(new Interface::UpstreamData::MagnetometerFrame);
    stClient->addExpectedDataType(std::move(magnetometerFrame));
    std::unique_ptr<Interface::UpstreamData::MovementInformationLeftRightFrame>pwmFrame(new Interface::UpstreamData::MovementInformationLeftRightFrame);
    stClient->addExpectedDataType(std::move(pwmFrame));
    std::unique_ptr<Interface::UpstreamData::PackageStatisticsFrame>packageStatisticsFrame(new Interface::UpstreamData::PackageStatisticsFrame);
    stClient->addExpectedDataType(std::move(packageStatisticsFrame));
    std::unique_ptr<Interface::UpstreamData::RFIDFrame>rfidframe(new Interface::UpstreamData::RFIDFrame);
    stClient->addExpectedDataType(std::move(rfidframe));
    std::unique_ptr<Interface::UpstreamData::ServiceTimeFrame>serviceTimeFrame(new Interface::UpstreamData::ServiceTimeFrame);
    stClient->addExpectedDataType(std::move(serviceTimeFrame));
    std::unique_ptr<Interface::UpstreamData::TimersFrame>timersFrame(new Interface::UpstreamData::TimersFrame);
    stClient->addExpectedDataType(std::move(timersFrame));
    std::unique_ptr<Interface::UpstreamData::TimeSyncFrame>timeSyncFrame(new Interface::UpstreamData::TimeSyncFrame);
    stClient->addExpectedDataType(std::move(timeSyncFrame));
    std::unique_ptr<Interface::UpstreamData::UltraSoundFrame> ultraSoundFrame(new Interface::UpstreamData::UltraSoundFrame);
    stClient->addExpectedDataType(std::move(ultraSoundFrame));

    stClient->run();

    return 0;
}


