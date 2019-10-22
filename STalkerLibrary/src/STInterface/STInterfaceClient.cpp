#include "STInterfaceClient.h"

#include <iostream>
#include <utility>
#include <algorithm>

#include <boost/asio.hpp>
#include <ros/console.h>

#include "../ROSInterface/ROSInterfaceClient.h"
#include "../DataExchanged/UpstreamData/GyroscopeFrame.h"


//std::list<std::unique_ptr<Interface::UpstreamDataType>> STInterface::STInterfaceClient::expectedDataTypes;

STInterface::STInterfaceClient::STInterfaceClient(boost::asio::ip::tcp iConnectionType, unsigned short iPort)
    : acceptor(ioService, boost::asio::ip::tcp::endpoint(iConnectionType, iPort ))
{
    ROS_INFO("ST Interface Client created");
}

//#TODO iExpectedDataType shall be of cost & type(to not recreate entire object again, even tho it's singular operation
void STInterface::STInterfaceClient::addExpectedDataType(std::unique_ptr<Interface::UpstreamDataType> iExpectedDataType)
{
    expectedDataTypes.push_back(std::move(iExpectedDataType));
    ROS_DEBUG("ST Interface enlisted new data type");
}

//void STInterface::STInterfaceClient::setROSInterface(ROSInterface::ROSInterfaceClient &client)
//{
//    ROSClient=client;
//}

void STInterface::STInterfaceClient::clear()
{
    expectedDataTypes.clear();
    ROS_DEBUG("ST Interface cleared expected data types list");
}

void STInterface::STInterfaceClient::run()
{
    start_accept();
    ioService.run();
}

void STInterface::STInterfaceClient::publishData(std::vector<uint8_t> iData)
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
    try
    {
        socket.connect( boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string("192.168.1.10"), 7 ));
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


void STInterface::STInterfaceClient::start_accept()
{
    Session* newSession = new Session(ioService);
    acceptor.async_accept(newSession->getSocket(),
                           boost::bind(&STInterface::STInterfaceClient::handle_accept, this, newSession,
                                       boost::asio::placeholders::error));
}

void STInterface::STInterfaceClient::handle_accept(Session* newSession,
                   const boost::system::error_code& error)
{
    if (!error)
    {
        for (auto ExpectedDataTypeIterator = expectedDataTypes.begin(); ExpectedDataTypeIterator != expectedDataTypes.end(); ExpectedDataTypeIterator++)
        {
            newSession->addExpectedDataType(ExpectedDataTypeIterator->get()->getClone());
        }

        newSession->start();
    }
    else
    {
        delete newSession;
    }

    start_accept();
}
