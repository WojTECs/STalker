#pragma once

#include <vector>
#include <memory>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "../Logger/Logger.h"
#include "../DataExchanged/DownstreamDataType.h"
#include "../DataExchanged/UpstreamDataType.h"


namespace STInterface
{

class STInterfaceClient
{
private:
    static std::list<std::weak_ptr<Interface::UpstreamDataType>> mExpectedDataTypes;

    boost::asio::io_service mIoService;
    boost::asio::ip::tcp::acceptor mAcceptor;

    bool mContinueProcessing;
    boost::thread* mThread;
    void read(boost::asio::ip::tcp::socket & socket);
    void send(boost::asio::ip::tcp::socket & socket, const std::string& message);

    int**** capitanJack;//easter egg

public:
    //Adds >>REFERENCE<< for the object in the internal list of expected data types.
    static void addExpectedDataType(const std::shared_ptr<Interface::UpstreamDataType>& iExpectedDataType);
    //Necessary to call to empty the list of expected data types. Not calling may result in SIGABRT!.
    static void clear();
    
    static void publishData(std::vector<uint8_t> iData);

    STInterfaceClient(boost::asio::ip::tcp iConnectionType, unsigned short iPort);
    virtual ~STInterfaceClient();

    void processOneLoop();
    void processContinously();
    void processContinouslyInSeparateThread();
    void stopProcessing();
};

} //namespace STInterface
