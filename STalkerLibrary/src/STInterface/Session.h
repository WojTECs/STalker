#pragma once

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <list>
#include "../DataExchanged/UpstreamDataType.h"
#include "../ROSInterface/ROSInterfaceClient.h"

//using namespace ROSInterface;

namespace STInterface
{

class Session
{
public:

    Session(boost::asio::io_service& io_service) : socket(io_service) {}
    virtual ~Session() {}

    boost::asio::ip::tcp::socket& getSocket() { return socket; }

    void start();
    void addExpectedDataType(std::unique_ptr<Interface::UpstreamDataType> iExpectedDataType);
    //void setROSInterface(ROSInterface::ROSInterfaceClient& client);

private:

    //ROSInterface::ROSInterfaceClient& client;
    void handleRead(const boost::system::error_code& error, size_t bytes_transferred);
    void handleWrite(const boost::system::error_code& error);

    std::list<std::unique_ptr<Interface::UpstreamDataType>> expectedDataTypes;

    boost::asio::ip::tcp::socket socket;
    enum { max_length = 1024 };
    char rawSocketData[max_length];
};

} //namespace STInterface
