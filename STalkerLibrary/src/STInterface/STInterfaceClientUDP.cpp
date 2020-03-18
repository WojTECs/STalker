#include "STInterfaceClientUDP.h"

#include <iostream>
#include <utility>
#include <algorithm>

#include <boost/asio.hpp>
#include <ros/console.h>

#include "../ROSInterface/ROSInterfaceClient.h"
#include "../DataExchanged/UpstreamData/GyroscopeFrame.h"


STInterface::STInterfaceClientUDP::STInterfaceClientUDP(unsigned short iPort, std::string stAddress, std::string stPort)
    : stAddress(stAddress),
      stPort(stPort),
      resolver(tcpIoService),
      udpSocket(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), iPort)),
      tcpSocket(tcpIoService),
      query(boost::asio::ip::tcp::v4(), stAddress.c_str(), stPort)
{
    ROS_INFO("ST Interface Client created");
    iterator = resolver.resolve(query);
    try
    {
        boost::asio::connect(tcpSocket, iterator);
    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        ROS_ERROR("ST Connection error. Boost says: %s", diag.c_str());
    }
}

void STInterface::STInterfaceClientUDP::addExpectedDataType(std::unique_ptr<Interface::UpstreamDataType> iExpectedDataType)
{
    //expectedDataTypes.push_back(std::move(iExpectedDataType));
    if(expectedDataTypesRegistry[iExpectedDataType->getProtocolIdentificator()]!=nullptr)
    {
        ROS_WARN("Error during enlisting new message type. This message ID is already occupied!");
    }
    expectedDataTypesRegistry[iExpectedDataType->getProtocolIdentificator()] = std::move(iExpectedDataType);
    ROS_DEBUG("STInterface session enlisted new data type");
}

void STInterface::STInterfaceClientUDP::setROSInterface(std::shared_ptr<ROSInterface::ROSInterfaceClient> client)
{
    ROSClient=client;
}

void STInterface::STInterfaceClientUDP::run()
{
    doReceive();
    ioService.run();
}

void STInterface::STInterfaceClientUDP::doReceive()
{
  udpSocket.async_receive_from(
      boost::asio::buffer(rawSocketData, max_length), senderEndpoint,
      [this](boost::system::error_code error, std::size_t bytesTransferred)
      {
        if (!error && bytesTransferred > 0)
        {
            int byteProcessed = 0;

            while(byteProcessed < bytesTransferred && bytesTransferred >= 2)
            {
                //reading first byte of a batch describing message type
                uint8_t batchMessageType = rawSocketData[byteProcessed];
                byteProcessed++;

                //reading first byte of a batch describing batch length expressed by a number of bytes following
                uint8_t batchMessageLength = rawSocketData[byteProcessed];
                byteProcessed++;

                //pass vector substring of data(of a given type)
                if(byteProcessed + batchMessageLength > bytesTransferred)
                {
                    ROS_ERROR("CRITICAL! STalker can't keep up with message processing, one frame is lost.");
                    break;
                }

                if(expectedDataTypesRegistry[batchMessageType]==nullptr)
                {
                    ROS_ERROR("Message buffer is getting full and one message got split apart, or bad message identifier was received.");
                    break;
                }

                expectedDataTypesRegistry[batchMessageType]->deserialize(rawSocketData + byteProcessed, batchMessageLength);
                expectedDataTypesRegistry[batchMessageType]->doTheProcessing();

                expectedDataTypesRegistry[batchMessageType]->sendData(*ROSClient);
                //ROSClient->publishString(expectedDataTypesRegistry[batchMessageType]->serialize(),
                //                       expectedDataTypesRegistry[batchMessageType]->getRosTopic());

                //moving processing index on the first byte of a next batch
                byteProcessed += batchMessageLength;
            }

          doReceive();
        }
      });
}

void STInterface::STInterfaceClientUDP::publishData(Interface::DownstreamDataType& iData)
{
    boost::system::error_code error;
    boost::asio::write( tcpSocket, boost::asio::buffer(iData.serialize()), error );
    if(error)
    {
        ROS_ERROR("ST tcp write error. Boost error message is: %s", std::string(error.message()).c_str());
        iterator = resolver.resolve(query);
        try
        {
            boost::asio::connect(tcpSocket, iterator);
        }
        catch (const boost::exception& e)
        {
            std::string diag = diagnostic_information(e);
            ROS_ERROR("ST Connection error. Boost says: %s", diag.c_str());
        }
    }
}
