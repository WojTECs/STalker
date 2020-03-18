#pragma once

#include <vector>
#include <memory>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "../DataExchanged/DownstreamDataType.h"
#include "../STInterface/Session.h"
#include "../DataExchanged/UpstreamDataType.h"
#include "../ROSInterface/ROSInterfaceClient.h"
#include "Session.h"

namespace ROSInterface
{
    class ROSInterfaceClient;
}

namespace Interface
{
    class UpstreamDataType;
}

namespace STInterface
{
    class Session;

class STInterfaceClientUDP
{
private:

    std::unique_ptr<Interface::UpstreamDataType> expectedDataTypesRegistry[256];

    std::shared_ptr<ROSInterface::ROSInterfaceClient> ROSClient;

    boost::asio::io_service tcpIoService;
    boost::asio::ip::tcp::resolver resolver;
    boost::asio::ip::tcp::socket tcpSocket;
    boost::asio::ip::tcp::resolver::query query;
    boost::asio::ip::tcp::resolver::iterator iterator;

    boost::asio::io_service ioService;

    std::string stAddress;//STM ip address
    std::string stPort;//STM receiving port

public:
    enum { max_length = 1024 };
    char rawSocketData[max_length];
    boost::asio::ip::udp::socket udpSocket;
    boost::asio::ip::udp::endpoint senderEndpoint;
    void doReceive();
    void doSend(std::size_t length);

    //Adds >>REFERENCE<< for the object in the internal list of expected data types.
    void addExpectedDataType(std::unique_ptr<Interface::UpstreamDataType> iExpectedDataType);
    void setROSInterface(std::shared_ptr<ROSInterface::ROSInterfaceClient> client);
    void run();
    void publishData(Interface::DownstreamDataType& iData);

    STInterfaceClientUDP(unsigned short iPort, std::string stAddress, std::string stPort);
    virtual ~STInterfaceClientUDP() {}

};

} //namespace STInterface
