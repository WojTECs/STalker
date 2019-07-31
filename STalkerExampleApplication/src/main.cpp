#include <iostream>
#include <string>
#include <memory>
#include <boost/asio.hpp>

#include "STalkerLibraryInterface.h"

using namespace std;

int main(int argv, char* argc[])
{
    STInterface::STInterfaceClient client(boost::asio::ip::tcp::v4(),1227);

    std::shared_ptr<STInterface::ExpectedDataTypes::AccelerometerFrame>accelerometerFrame(new STInterface::ExpectedDataTypes::AccelerometerFrame);
    client.addExpectedDataType(accelerometerFrame);
    std::shared_ptr<STInterface::ExpectedDataTypes::EncoderFrame>encoderFrame(new STInterface::ExpectedDataTypes::EncoderFrame);
    client.addExpectedDataType(encoderFrame);
    std::shared_ptr<STInterface::ExpectedDataTypes::GPSFrame>gpsFrame(new STInterface::ExpectedDataTypes::GPSFrame);
    client.addExpectedDataType(gpsFrame);
    std::shared_ptr<STInterface::ExpectedDataTypes::GyroscopeFrame>gyroscopeFrame(new STInterface::ExpectedDataTypes::GyroscopeFrame);
    client.addExpectedDataType(gyroscopeFrame);
    std::shared_ptr<STInterface::ExpectedDataTypes::MagnetometerFrame>magnetometerFrame(new STInterface::ExpectedDataTypes::MagnetometerFrame);
    client.addExpectedDataType(magnetometerFrame);
    std::shared_ptr<STInterface::ExpectedDataTypes::PWMFrame>pwmFrame(new STInterface::ExpectedDataTypes::PWMFrame);
    client.addExpectedDataType(pwmFrame);
    std::shared_ptr<STInterface::ExpectedDataTypes::TimersFrame>timersFrame(new STInterface::ExpectedDataTypes::TimersFrame);
    client.addExpectedDataType(timersFrame);

    client.processContinouslyInSeparateThread();


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


