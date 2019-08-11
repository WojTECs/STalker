#include <memory>

#include "STalkerLibraryInterface.h"

int main(int argc, char **argv)
{

    ros::init(argc, argv, "STalker");

    ROSInterface::ROSInterfaceClient rosClient;

    std::shared_ptr<STInterface::STInterfaceClient> stClient;

    try
    {
        stClient = std::make_shared<STInterface::STInterfaceClient>(boost::asio::ip::tcp::v4(),1228);
    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        ROS_FATAL("Bad IMU frame received. Boost says: %s", diag.c_str());
        return 0;
    }


    std::shared_ptr<Interface::DownstreamData::IMUFrame> imuFrame(new Interface::DownstreamData::IMUFrame);
    rosClient.addExpectedDataType(imuFrame);
    std::shared_ptr<Interface::DownstreamData::MovementFrame> movementFrame(new Interface::DownstreamData::MovementFrame);
    rosClient.addExpectedDataType(movementFrame);
    std::shared_ptr<Interface::DownstreamData::TimerConfigurationFrame> timerConfigurationFrame(new Interface::DownstreamData::TimerConfigurationFrame);
    rosClient.addExpectedDataType(timerConfigurationFrame);

    std::shared_ptr<Interface::UpstreamData::AccelerometerFrame>accelerometerFrame(new Interface::UpstreamData::AccelerometerFrame);
    stClient->addExpectedDataType(accelerometerFrame);
    std::shared_ptr<Interface::UpstreamData::EncoderFrame>encoderFrame(new Interface::UpstreamData::EncoderFrame);
    stClient->addExpectedDataType(encoderFrame);
    std::shared_ptr<Interface::UpstreamData::GPSFrame>gpsFrame(new Interface::UpstreamData::GPSFrame);
    stClient->addExpectedDataType(gpsFrame);
    std::shared_ptr<Interface::UpstreamData::GyroscopeFrame>gyroscopeFrame(new Interface::UpstreamData::GyroscopeFrame);
    stClient->addExpectedDataType(gyroscopeFrame);
    std::shared_ptr<Interface::UpstreamData::MagnetometerFrame>magnetometerFrame(new Interface::UpstreamData::MagnetometerFrame);
    stClient->addExpectedDataType(magnetometerFrame);
    std::shared_ptr<Interface::UpstreamData::PWMFrame>pwmFrame(new Interface::UpstreamData::PWMFrame);
    stClient->addExpectedDataType(pwmFrame);
    std::shared_ptr<Interface::UpstreamData::TimersFrame>timersFrame(new Interface::UpstreamData::TimersFrame);
    stClient->addExpectedDataType(timersFrame);

    stClient->processContinouslyInSeparateThread();

    while(1){}
    return 0;
}


