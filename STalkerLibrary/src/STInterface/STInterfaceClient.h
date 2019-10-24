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

namespace STInterface
{
    class Session;
}

namespace STInterface
{

class STInterfaceClient
{
private:

    // sword raptor pirate
    //#TODO - dodanie nowego message'a dla pbl i Ziembinskiego pirate4wd

    std::list<std::unique_ptr<Interface::UpstreamDataType>> expectedDataTypes;

    std::shared_ptr<ROSInterface::ROSInterfaceClient> ROSClient;

    boost::asio::io_service ioService;
    boost::asio::ip::tcp::acceptor acceptor;

    bool continueProcessing;
    boost::thread* thread;
    std::string stAddress;//STM ip address
    std::string stPort;//STM receiving port
    void read(boost::asio::ip::tcp::socket & socket);
    void send(boost::asio::ip::tcp::socket & socket, const std::string& message);
    void start_accept();
    void handle_accept(Session* new_session, const boost::system::error_code& error);

public:

    //Adds >>REFERENCE<< for the object in the internal list of expected data types.
    void addExpectedDataType(std::unique_ptr<Interface::UpstreamDataType> iExpectedDataType);
    void setROSInterface(std::shared_ptr<ROSInterface::ROSInterfaceClient> client);
    void clear();
    void run();
    void publishData(Interface::DownstreamDataType& iData);

    STInterfaceClient(boost::asio::ip::tcp iConnectionType, unsigned short iPort, std::string stAddress, std::string stPort);
    virtual ~STInterfaceClient() {}

};

} //namespace STInterface
