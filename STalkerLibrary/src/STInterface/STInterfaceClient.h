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

namespace STInterface
{

class STInterfaceClient
{
private:

    std::list<std::unique_ptr<Interface::UpstreamDataType>> expectedDataTypes;

    //ROSInterface::ROSInterfaceClient& ROSClient;

    boost::asio::io_service ioService;
    boost::asio::ip::tcp::acceptor acceptor;

    bool continueProcessing;
    boost::thread* thread;
    void read(boost::asio::ip::tcp::socket & socket);
    void send(boost::asio::ip::tcp::socket & socket, const std::string& message);

public:

    //Adds >>REFERENCE<< for the object in the internal list of expected data types.
    void addExpectedDataType(std::unique_ptr<Interface::UpstreamDataType> iExpectedDataType);

    //void setROSInterface(ROSInterface::ROSInterfaceClient& ROSClient);
    //Necessary to call to empty the list of expected data types. Not calling may result in SIGABRT!.
    void clear();
    void run();
    
    void publishData(std::vector<uint8_t> iData);

    STInterfaceClient(boost::asio::ip::tcp iConnectionType, unsigned short iPort);
    virtual ~STInterfaceClient() {}

    void processOneLoop();
    void processContinously();
    void processContinouslyInSeparateThread();
    void stopProcessing();


private:
    void start_accept();

    void handle_accept(Session* new_session, const boost::system::error_code& error);

};

} //namespace STInterface
