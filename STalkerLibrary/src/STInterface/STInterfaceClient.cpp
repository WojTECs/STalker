#include "STInterfaceClient.h"
#include "Logger/Logger.h"

#include <iostream>
#include <boost/asio.hpp>

#include "../ROSInterface/ROSInterfaceClient.h"

#include "../DataExchanged/UpstreamData/GyroscopeFrame.h"


STInterface::STInterfaceClient::STInterfaceClient(boost::asio::ip::tcp iConnectionType, unsigned short iPort)
    :
      mAcceptor(mIoService, boost::asio::ip::tcp::endpoint(iConnectionType, iPort ))
{}

STInterface::STInterfaceClient::~STInterfaceClient(){}

std::list<std::weak_ptr<Interface::UpstreamDataType>> STInterface::STInterfaceClient::mExpectedDataTypes;

//=======================================================================
//
void STInterface::STInterfaceClient::addExpectedDataType(const std::shared_ptr<Interface::UpstreamDataType> &iExpectedDataType)
{
    mExpectedDataTypes.push_back(iExpectedDataType);
}

//=======================================================================
//
void STInterface::STInterfaceClient::clear()
{
    mExpectedDataTypes.clear();
}


using namespace boost::asio;


void STInterface::STInterfaceClient::publishData(std::vector<uint8_t> iData)
{
    //#TODO refactor
    boost::asio::io_service io_service;
    ip::tcp::socket socket(io_service);
    try
    {
         socket.connect( ip::tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 45455 ));
    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        //#TODO log error

    }


    boost::system::error_code error;
    boost::asio::write( socket, boost::asio::buffer(iData), error );
    if( !error )
    {
        //#TODO implement
    }
}

//#TODO: general logging everywhere
//#TODO: general clearance
void STInterface::STInterfaceClient::read(boost::asio::ip::tcp::socket & socket)
{

    boost::asio::streambuf initialDataBuffer;

    //#TODO refactor - its ugly
    //#TODO: error logging/handling sratatat
    //code below is ugly... but proper buffer_copy didn't wanted to work, and nobody pays me for that project...
    boost::system::error_code error;
    boost::asio::read( socket, initialDataBuffer, boost::asio::transfer_exactly(2), error );

    const uint8_t* messageTypePtr = boost::asio::buffer_cast<const uint8_t*>(initialDataBuffer.data());

    //first send byte describes the data type that's about to be sent
    uint8_t messageType = messageTypePtr[0];
    uint8_t messageByteCount = messageTypePtr[1];

    //#TODO - what if expected data type id or size == 0
    for (auto ExpectedDataTypeIterator = mExpectedDataTypes.begin(); ExpectedDataTypeIterator != mExpectedDataTypes.end(); ExpectedDataTypeIterator++)
    {
        //Checkup whether reference still exists
        std::shared_ptr<Interface::UpstreamDataType> ExpectedDataTypeSharedBond;
        ExpectedDataTypeSharedBond = ExpectedDataTypeIterator->lock();

        //if reference exists, and message type is correct
        if(ExpectedDataTypeSharedBond)
        {
            if(ExpectedDataTypeSharedBond->getProtocolIdentificator() == messageType)
            {
                boost::asio::streambuf actuallDataBuffer;
                //read as much as is told by messageByteCount
                boost::asio::read( socket,
                                   actuallDataBuffer,
                                   boost::asio::transfer_exactly(messageByteCount),
                                   error);

                const uint8_t* messageTypePtr = boost::asio::buffer_cast<const uint8_t*>(actuallDataBuffer.data());

                //messageTypePtr+1 and bin size +1 cause the first byte is a fame type - it's unwanted in the vector
                std::vector<uint8_t> oDataRead(messageTypePtr, messageTypePtr+messageByteCount);

                ExpectedDataTypeSharedBond->deserialize(oDataRead);
                ExpectedDataTypeSharedBond->doTheProcessing();

                ROSInterface::ROSInterfaceClient::publishData(*ExpectedDataTypeSharedBond);
            }
        }
        else
        {
            mExpectedDataTypes.erase(ExpectedDataTypeIterator);
        }
    }
}

void STInterface::STInterfaceClient::send(boost::asio::ip::tcp::socket & socket, const std::string& message)
{
    const std::string msg = message + "\n";
    boost::asio::write( socket, boost::asio::buffer(message) );
}


void STInterface::STInterfaceClient::processOneLoop()
{
    boost::asio::ip::tcp::socket socket(mIoService);
    mAcceptor.accept(socket);
    read(socket);
    send(socket, "");
}

void STInterface::STInterfaceClient::processContinously()
{
    mContinueProcessing = true;
    while(mContinueProcessing == true)
    {
        processOneLoop();
    }
}

void STInterface::STInterfaceClient::processContinouslyInSeparateThread()
{
    mThread = new boost::thread(boost::bind(&STInterface::STInterfaceClient::processContinously, this));
}

void STInterface::STInterfaceClient::stopProcessing()
{
    mContinueProcessing = false;
}
