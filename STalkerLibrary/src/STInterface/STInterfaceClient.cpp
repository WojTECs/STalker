#include "STInterfaceClient.h"

#include <iostream>

#include <boost/asio.hpp>
#include <ros/console.h>

#include "../ROSInterface/ROSInterfaceClient.h"
#include "../DataExchanged/UpstreamData/GyroscopeFrame.h"

std::list<std::weak_ptr<Interface::UpstreamDataType>> STInterface::STInterfaceClient::expectedDataTypes;

STInterface::STInterfaceClient::STInterfaceClient(boost::asio::ip::tcp iConnectionType, unsigned short iPort)
    : acceptor(ioService, boost::asio::ip::tcp::endpoint(iConnectionType, iPort ))
{
    ROS_INFO("ST Interface Client created");
}

STInterface::STInterfaceClient::~STInterfaceClient()
{

}

void STInterface::STInterfaceClient::addExpectedDataType(const std::shared_ptr<Interface::UpstreamDataType> &iExpectedDataType)
{

    expectedDataTypes.push_back(iExpectedDataType);
    ROS_DEBUG("ST Interface enlisted new data type");
}

void STInterface::STInterfaceClient::clear()
{
    expectedDataTypes.clear();
    ROS_DEBUG("ST Interface cleared expected data types list");
}

void STInterface::STInterfaceClient::publishData(std::vector<uint8_t> iData)
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
    try
    {
        socket.connect( boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 45455 ));
    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        ROS_ERROR("ST Connection error. Boost says: %s", diag.c_str());

    }

    boost::system::error_code error;
    boost::asio::write( socket, boost::asio::buffer(iData), error );
    if( !error )
    {
        ROS_ERROR("ST tcp write error. Reason unknown.");
    }
}

void STInterface::STInterfaceClient::read(boost::asio::ip::tcp::socket & socket)
{

    boost::asio::streambuf initialDataBuffer;

    boost::system::error_code error;
    boost::asio::read( socket, initialDataBuffer, boost::asio::transfer_exactly(2), error );

    const uint8_t* messageTypePtr = boost::asio::buffer_cast<const uint8_t*>(initialDataBuffer.data());

    //first sent byte describes the data type that's about to be sent
    uint8_t messageType = messageTypePtr[0];
    //second byte describes the length
    uint8_t messageByteCount = messageTypePtr[1];

    for (auto ExpectedDataTypeIterator = expectedDataTypes.begin(); ExpectedDataTypeIterator != expectedDataTypes.end(); ExpectedDataTypeIterator++)
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
            expectedDataTypes.erase(ExpectedDataTypeIterator);
            ROS_ERROR("ST interface found empty reference on the expected data types list");
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
    boost::asio::ip::tcp::socket socket(ioService);
    acceptor.accept(socket);
    read(socket);
    send(socket, "");
}

void STInterface::STInterfaceClient::processContinously()
{
    ROS_DEBUG("ST Interface Client begins continous processing");
    continueProcessing = true;
    while(continueProcessing == true)
    {
        processOneLoop();
    }
}

void STInterface::STInterfaceClient::processContinouslyInSeparateThread()
{
    thread = new boost::thread(boost::bind(&STInterface::STInterfaceClient::processContinously, this));
}

void STInterface::STInterfaceClient::stopProcessing()
{
    continueProcessing = false;
}
