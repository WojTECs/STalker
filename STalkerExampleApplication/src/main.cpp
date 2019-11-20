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
        stClient = std::make_shared<STInterface::STInterfaceClientUDP>(22336, "192.168.1.10", "7");//192.168.1.10", "7");
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

    std::unique_ptr<Interface::DownstreamData::IMUFrame> imuFrame(new Interface::DownstreamData::IMUFrame);
    rosClient->addExpectedDataType(std::move(imuFrame));
    std::unique_ptr<Interface::DownstreamData::MovementOrderTurnPropulsionFrame> movementFrame(new Interface::DownstreamData::MovementOrderTurnPropulsionFrame);
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
    std::unique_ptr<Interface::UpstreamData::MovementInformationTurnPropulsionFrame>pwmFrame(new Interface::UpstreamData::MovementInformationTurnPropulsionFrame);
    stClient->addExpectedDataType(std::move(pwmFrame));
    std::unique_ptr<Interface::UpstreamData::TimersFrame>timersFrame(new Interface::UpstreamData::TimersFrame);
    stClient->addExpectedDataType(std::move(timersFrame));

    stClient->run();

    return 0;
}


