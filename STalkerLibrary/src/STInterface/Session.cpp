#include "Session.h"

STInterface::Session::Session(boost::asio::io_service &io_service) : socket(io_service) {}

void STInterface::Session::start()
{
    socket.async_read_some(boost::asio::buffer(rawSocketData, max_length),
                            boost::bind(&Session::handleRead, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void STInterface::Session::addExpectedDataType(std::unique_ptr<Interface::UpstreamDataType> iExpectedDataType)
{

    //expectedDataTypes.push_back(std::move(iExpectedDataType));
    if(expectedDataTypesRegistry[iExpectedDataType->getProtocolIdentificator()]!=nullptr)
    {
        ROS_WARN("Error during enlisting new message type. This message ID is already occupied!");
    }
    expectedDataTypesRegistry[iExpectedDataType->getProtocolIdentificator()] = std::move(iExpectedDataType);
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
        //std::vector<uint8_t> data(rawSocketData, rawSocketData + bytesTransferred);
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

            expectedDataTypesRegistry[batchMessageType]->deserialize(rawSocketData, batchMessageLength);
            expectedDataTypesRegistry[batchMessageType]->doTheProcessing();

            ROSClient->publishData(expectedDataTypesRegistry[batchMessageType]->serialize(),
                                   expectedDataTypesRegistry[batchMessageType]->getRosTopic());

            //moving processing index on the first byte of a next batch
            byteProcessed += batchMessageLength;
        }

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
