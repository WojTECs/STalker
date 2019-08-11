#include <iostream>
#include <string>
#include <memory>
#include <boost/asio.hpp>
#include "ros/ros.h"
#include "std_msgs/String.h"

#include "STalkerLibraryInterface.h"

using namespace std;


#include <sstream>


int main(int argc, char **argv)
{
    ros::init(argc, argv, "STalker");

    ROSInterface::ROSInterfaceClient rosClient;

    //#TODO remove
    rosClient.b=1;
    //#TODO add exception handling for situation where port is occupied
    STInterface::STInterfaceClient stClient(boost::asio::ip::tcp::v4(),1228);

    std::shared_ptr<Interface::DownstreamData::IMUFrame>imuFrame(new Interface::DownstreamData::IMUFrame);
    rosClient.addExpectedDataType(imuFrame);

    std::shared_ptr<Interface::UpstreamData::AccelerometerFrame>accelerometerFrame(new Interface::UpstreamData::AccelerometerFrame);
    stClient.addExpectedDataType(accelerometerFrame);
    std::shared_ptr<Interface::UpstreamData::EncoderFrame>encoderFrame(new Interface::UpstreamData::EncoderFrame);
    stClient.addExpectedDataType(encoderFrame);
    std::shared_ptr<Interface::UpstreamData::GPSFrame>gpsFrame(new Interface::UpstreamData::GPSFrame);
    stClient.addExpectedDataType(gpsFrame);
    std::shared_ptr<Interface::UpstreamData::GyroscopeFrame>gyroscopeFrame(new Interface::UpstreamData::GyroscopeFrame);
    stClient.addExpectedDataType(gyroscopeFrame);
    std::shared_ptr<Interface::UpstreamData::MagnetometerFrame>magnetometerFrame(new Interface::UpstreamData::MagnetometerFrame);
    stClient.addExpectedDataType(magnetometerFrame);
    std::shared_ptr<Interface::UpstreamData::PWMFrame>pwmFrame(new Interface::UpstreamData::PWMFrame);
    stClient.addExpectedDataType(pwmFrame);
    std::shared_ptr<Interface::UpstreamData::TimersFrame>timersFrame(new Interface::UpstreamData::TimersFrame);
    stClient.addExpectedDataType(timersFrame);

    stClient.processContinouslyInSeparateThread();


    std::shared_ptr<STalker::LogUtils::LoggingInterface> terminalLogger(new STalker::LogUtils::TerminalLogger);
    STalker::Logger::addLogger(terminalLogger);

    std::shared_ptr<STalker::LogUtils::LoggingInterface> tcpLogger(new STalker::LogUtils::TCPLogger);
    STalker::Logger::addLogger(tcpLogger);

    std::shared_ptr<STalker::LogUtils::LoggingInterface> fileLogger(new STalker::LogUtils::FileLogger);
    STalker::Logger::addLogger(fileLogger);

    STalker::Logger::logMessage(LogImportanceLevel::Fatal,L"Fatal Error");
    STalker::Logger::logMessage(LogImportanceLevel::Error,L"Error");
    STalker::Logger::logMessage(LogImportanceLevel::Debug,L"Debug");
    STalker::Logger::logMessage(LogImportanceLevel::Info,L"Info");

    STalker::Logger::clear();
    while(1){}
    return 0;
}


