#pragma once

#include <netinet/in.h>

#include "../LoggingInterface.h"
#include "../Logger.h"

namespace STalker  {
namespace LogUtils  {

//Brilliant utility for getting log through lan- most basic client can be netcat (command: nc -klp <port>)


class TCPLogger : public LoggingInterface
{
private:
  sockaddr_in mServerAddress;
  int mPort;
  int mSocketFileDescriptor;
public:
    TCPLogger(const std::string iAddress = "localhost", const int iPort = 1226);
    virtual ~TCPLogger() override;

    void logMessage(const enum LogImportanceLevel& iLogLevel,const std::wstring& iMessage) override;
};

} //namespace LogUtils
} //namespace STalker
