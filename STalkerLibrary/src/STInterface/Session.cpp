#include "Session.h"

void STInterface::Session::start()
{
    socket.async_read_some(boost::asio::buffer(rawSocketData, max_length),
                            boost::bind(&Session::handleRead, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void STInterface::Session::addExpectedDataType(std::unique_ptr<Interface::UpstreamDataType> iExpectedDataType)
{

    expectedDataTypes.push_back(std::move(iExpectedDataType));
    ROS_DEBUG("STInterface session enlisted new data type");
}

void STInterface::Session::setROSInterface(std::shared_ptr<ROSInterface::ROSInterfaceClient> client)
{
    ROSClient=client;
}

void STInterface::Session::handleRead(const boost::system::error_code& error, size_t bytesTransferred)
{
    if (!error)
    {
        std::vector<uint8_t> data(rawSocketData, rawSocketData + bytesTransferred);
        int byteProcessed = 0;

        while(byteProcessed != bytesTransferred && bytesTransferred >= 2)
        {
            if(byteProcessed > bytesTransferred)
                ROS_ERROR("CRITICAL! Value describing Byte processed got bigger than bytes transferred");

            //reading first byte of a batch describing message type
            uint8_t batchMessageType = data[byteProcessed];
            byteProcessed++;

            //reading first byte of a batch describing batch length expressed by a number of bytes following
            uint8_t batchMessageLength = data[byteProcessed];
            byteProcessed++;

            for (auto expectedDataTypeIterator = expectedDataTypes.begin(); expectedDataTypeIterator != expectedDataTypes.end(); expectedDataTypeIterator++)
            {

                if(expectedDataTypeIterator->get()->getProtocolIdentificator() == batchMessageType)
                {
                    //pass vector substring of data(of a given type)
                    if(byteProcessed + batchMessageLength > bytesTransferred)
                    {
                        ROS_ERROR("CRITICAL! STalker can't keep up with message processing, one frame is lost.");
                        byteProcessed == bytesTransferred;
                        break;
                    }

                    expectedDataTypeIterator->get()->deserialize(std::vector<uint8_t>(data.begin() + byteProcessed,
                                                                                 data.begin() + byteProcessed + batchMessageLength));
                    expectedDataTypeIterator->get()->doTheProcessing();

                    ROSClient->publishData(expectedDataTypeIterator->get()->serialize(),
                                           expectedDataTypeIterator->get()->getRosTopic());
                }
            }

            //moving processing index on the first byte of a next batch
            byteProcessed += batchMessageLength;
        }

//NOTICE!!! If you want the server to send some reply, comment out code below, and uncomment async_write function call
        socket.async_read_some(boost::asio::buffer(rawSocketData, max_length),
                                boost::bind(&Session::handleRead, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));

//UNCOMMENT BELOW
//
//        boost::asio::async_write(socket,//#TODO - change data sent in the response
//                                 boost::asio::buffer(rawSocketData, bytesTransferred),
//                                 boost::bind(&Session::handleWrite, this,
//                                             boost::asio::placeholders::error));
    }
    else
    {
        delete this;
    }
}

void STInterface::Session::handleWrite(const boost::system::error_code& error)
{
    if (!error)
    {
        socket.async_read_some(boost::asio::buffer(rawSocketData, max_length),
                                boost::bind(&Session::handleRead, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        delete this;
    }
}
