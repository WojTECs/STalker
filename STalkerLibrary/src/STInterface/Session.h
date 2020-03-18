#pragma once

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <list>
#include "../DataExchanged/UpstreamDataType.h"
#include "../ROSInterface/ROSInterfaceClient.h"

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

class Session
{
public:

    Session(boost::asio::io_service& io_service);
    virtual ~Session() {}

    boost::asio::ip::tcp::socket& getSocket() { return socket; }

    void start();
    void addExpectedDataType(std::unique_ptr<Interface::UpstreamDataType> iExpectedDataType);
    void setROSInterface(std::shared_ptr<ROSInterface::ROSInterfaceClient> client);

private:

    std::shared_ptr<ROSInterface::ROSInterfaceClient> ROSClient;
    void handleRead(const boost::system::error_code& error, size_t bytes_transferred);
    void handleWrite(const boost::system::error_code& error);

    std::unique_ptr<Interface::UpstreamDataType> expectedDataTypesRegistry[256];

    boost::asio::ip::tcp::socket socket;
    enum { max_length = 8000 };
    char rawSocketData[max_length];
};

} //namespace STInterface
