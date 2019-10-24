#include <memory>

#include "STalkerLibraryInterface.h"

int main(int argc, char **argv)
{

    ros::init(argc, argv, "STalker");

    std::shared_ptr<ROSInterface::ROSInterfaceClient> rosClient;
    std::shared_ptr<STInterface::STInterfaceClient> stClient;

    try
    {
        stClient = std::make_shared<STInterface::STInterfaceClient>(boost::asio::ip::tcp::v4(), 1238, "localhost", "34567");
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

    std::unique_ptr<Interface::DownstreamData::IMUFrame> imuFrame(new Interface::DownstreamData::IMUFrame);
    rosClient->addExpectedDataType(std::move(imuFrame));
    std::unique_ptr<Interface::DownstreamData::MovementFrameTurnPropulsion> movementFrame(new Interface::DownstreamData::MovementFrameTurnPropulsion);
    rosClient->addExpectedDataType(std::move(movementFrame));
    std::unique_ptr<Interface::DownstreamData::TimerConfigurationFrame> timerConfigurationFrame(new Interface::DownstreamData::TimerConfigurationFrame);
    rosClient->addExpectedDataType(std::move(timerConfigurationFrame));

    std::unique_ptr<Interface::UpstreamData::AccelerometerFrame>accelerometerFrame(new Interface::UpstreamData::AccelerometerFrame);
    stClient->addExpectedDataType(std::move(accelerometerFrame));
    std::unique_ptr<Interface::UpstreamData::EncoderFrame>encoderFrame(new Interface::UpstreamData::EncoderFrame);
    stClient->addExpectedDataType(std::move(encoderFrame));
    std::unique_ptr<Interface::UpstreamData::GPSFrame>gpsFrame(new Interface::UpstreamData::GPSFrame);
    stClient->addExpectedDataType(std::move(gpsFrame));
    std::unique_ptr<Interface::UpstreamData::GyroscopeFrame>gyroscopeFrame(new Interface::UpstreamData::GyroscopeFrame);
    stClient->addExpectedDataType(std::move(gyroscopeFrame));
    std::unique_ptr<Interface::UpstreamData::MagnetometerFrame>magnetometerFrame(new Interface::UpstreamData::MagnetometerFrame);
    stClient->addExpectedDataType(std::move(magnetometerFrame));
    std::unique_ptr<Interface::UpstreamData::PWMFrame>pwmFrame(new Interface::UpstreamData::PWMFrame);
    stClient->addExpectedDataType(std::move(pwmFrame));
    std::unique_ptr<Interface::UpstreamData::TimersFrame>timersFrame(new Interface::UpstreamData::TimersFrame);
    stClient->addExpectedDataType(std::move(timersFrame));

    stClient->run();

    return 0;
}


