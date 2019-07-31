#include "TCPLogger.h"

#include <sys/socket.h>
#include <cstdlib>
#include <sys/unistd.h>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <strings.h>
#include <cstring>

#include <signal.h>

#include <iostream>

#include <errno.h>

#include <arpa/inet.h>




using namespace STalker::LogUtils;


//=======================================================================
//
TCPLogger::TCPLogger(const std::string iAddress, const int iPort) : mPort(iPort)
{
    //host entity creation and verification
    struct hostent* server;
    server = gethostbyname(iAddress.c_str());

    if (server == nullptr)
    {
        this->setEnable(false);//Turn off this logging interface. Ommitting that may result in infinite recurrency!
        STalker::Logger::logMessage(LogImportanceLevel::Error,L"TCPLogger: No such address.");
        return;
    }

    //Server address entity creation and verification
    mServerAddress.sin_family = AF_INET;
    inet_ntop(AF_INET, &(mServerAddress.sin_addr),server->h_addr, static_cast<socklen_t>(server->h_length));
    mServerAddress.sin_port = htons(static_cast<uint16_t>(iPort));
}

//=======================================================================
//
TCPLogger::~TCPLogger()
{}

//=======================================================================
//
void TCPLogger::logMessage(const LogImportanceLevel& iLogLevel,const std::wstring& iMessage)
{
    if(this->isEnabled() && iLogLevel >= minLogImportanceLevel())
    {
        //Socket initialization
        mSocketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (mSocketFileDescriptor < 0)
        {
            this->setEnable(false);//Turn off this logging interface
            STalker::Logger::logMessage(LogImportanceLevel::Error,L"TCPLogger: Opening socket failed.");
            return;
        }

        //Connection establishment
        if (connect(mSocketFileDescriptor, reinterpret_cast<sockaddr*>(&mServerAddress), sizeof(mServerAddress)) < 0)
        {
            this->setEnable(false);//Turn off this logging interface
            STalker::Logger::logMessage(LogImportanceLevel::Error,L"TCPLogger: Connection trouble.");
            return;
        }

        ssize_t result = write(mSocketFileDescriptor,iMessage.c_str(), static_cast<size_t>(iMessage.size() * sizeof(wchar_t)));

        if (result < 0)
             std::cout<<"TCPLogger: Can't write to socket.";

        close(mSocketFileDescriptor);
    }
}
