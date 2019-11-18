#include "STInterfaceClientTCP.h"

#include <iostream>
#include <utility>
#include <algorithm>

#include <boost/asio.hpp>
#include <ros/console.h>

#include "../ROSInterface/ROSInterfaceClient.h"
#include "../DataExchanged/UpstreamData/GyroscopeFrame.h"


STInterface::STInterfaceClientTCP::STInterfaceClientTCP(unsigned short iPort, std::string stAddress, std::string stPort)
    : acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), iPort )),
      stAddress(stAddress),
      stPort(stPort),
      resolver(io_service),
      socket(io_service),
      query(boost::asio::ip::tcp::v4(), stAddress.c_str(), stPort)
{
    ROS_INFO("ST Interface Client created");
    iterator = resolver.resolve(query);
    try
    {
        boost::asio::connect(socket, iterator);
    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        ROS_ERROR("ST Connection error. Boost says: %s", diag.c_str());
    }

}

void STInterface::STInterfaceClientTCP::addExpectedDataType(std::unique_ptr<Interface::UpstreamDataType> iExpectedDataType)
{
    expectedDataTypes.push_back(std::move(iExpectedDataType));
    ROS_DEBUG("ST Interface enlisted new data type");
}

void STInterface::STInterfaceClientTCP::setROSInterface(std::shared_ptr<ROSInterface::ROSInterfaceClient> client)
{
    ROSClient=client;
}

void STInterface::STInterfaceClientTCP::clear()
{
    expectedDataTypes.clear();
    ROS_DEBUG("ST Interface cleared expected data types list");
}

void STInterface::STInterfaceClientTCP::run()
{
    start_accept();
    ioService.run();
}

void STInterface::STInterfaceClientTCP::publishData(Interface::DownstreamDataType& iData)
{


    boost::system::error_code error;
    boost::asio::write( socket, boost::asio::buffer(iData.serialize()), error );
    if(error)
    {
        ROS_ERROR("ST tcp write error. Boost error message is: %s", std::string(error.message()).c_str());
        iterator = resolver.resolve(query);
        try
        {
            boost::asio::connect(socket, iterator);
        }
        catch (const boost::exception& e)
        {
            std::string diag = diagnostic_information(e);
            ROS_ERROR("ST Connection error. Boost says: %s", diag.c_str());
        }
    }
}


void STInterface::STInterfaceClientTCP::start_accept()
{
    Session* newSession = new Session(ioService);
    acceptor.async_accept(newSession->getSocket(),
                           boost::bind(&STInterface::STInterfaceClientTCP::handle_accept, this, newSession,
                                       boost::asio::placeholders::error));
}

void STInterface::STInterfaceClientTCP::handle_accept(Session* newSession,
                   const boost::system::error_code& error)
{
    if (!error)
    {
        for (auto ExpectedDataTypeIterator = expectedDataTypes.begin(); ExpectedDataTypeIterator != expectedDataTypes.end(); ExpectedDataTypeIterator++)
        {
            newSession->addExpectedDataType(ExpectedDataTypeIterator->get()->getClone());
        }
        newSession->setROSInterface(ROSClient);
        newSession->start();
    }
    else
    {
        delete newSession;
    }

    start_accept();
}
