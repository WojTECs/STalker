//#include "STInterfaceClient.h"
//#include "Logger/Logger.h"

//#include <iostream>
//#include <boost/asio.hpp>

//#include "ExpectedDataTypes/GyroscopeFrame.h"

//STInterface::STInterfaceClient::STInterfaceClient(boost::asio::ip::tcp iConnectionType, unsigned short iPort)
//    :
//      mAcceptor(mIoService, boost::asio::ip::tcp::endpoint(iConnectionType, iPort ))
//{
//    //mAcceptor.accept(mSocket);
//}

//STInterface::STInterfaceClient::~STInterfaceClient(){}

//std::list<std::weak_ptr<STInterface::ExpectedDataType>> STInterface::STInterfaceClient::mExpectedDataTypes;

////=======================================================================
////
//void STInterface::STInterfaceClient::addExpectedDataType(const std::shared_ptr<STInterface::ExpectedDataType> &iExpectedDataType)
//{
//    mExpectedDataTypes.push_back(iExpectedDataType);
//}

////=======================================================================
////
//void STInterface::STInterfaceClient::clear()
//{
//    mExpectedDataTypes.clear();
//}

//void STInterface::STInterfaceClient::read(boost::asio::ip::tcp::socket & socket)
//{

//    boost::asio::streambuf buffer;

//    //#TODO: error logging/handling sratatat
//    //code below is ugly... but proper buffer_copy didn't wanted to work, and nobody pays me for that project...
//    boost::system::error_code error;
//    boost::asio::read( socket, buffer, boost::asio::transfer_exactly(1), error );

//    const uint8_t* messageTypePtr = boost::asio::buffer_cast<const uint8_t*>(buffer.data());

//    //first send byte describes the data type that's about to be sent
//    uint8_t messageType = messageTypePtr[0];

//    //#TODO - what if expected data type id or size == 0
//    for (auto ExpectedDataTypeIterator = mExpectedDataTypes.begin(); ExpectedDataTypeIterator != mExpectedDataTypes.end(); ExpectedDataTypeIterator++)
//    {
//        //Checkup whether reference still exists
//        std::shared_ptr<STInterface::ExpectedDataType> ExpectedDataTypeSharedBond;
//        ExpectedDataTypeSharedBond = ExpectedDataTypeIterator->lock();

//        //if reference exists, and message type is correct
//        if(ExpectedDataTypeSharedBond)
//        {
//            if(ExpectedDataTypeSharedBond->getProtocolIdentificator() == messageType)
//            {
//                //read as much as the object shall have
//                boost::asio::read( socket,
//                                   buffer,
//                                   boost::asio::transfer_exactly(ExpectedDataTypeSharedBond->getSTBinarySize()),
//                                   error);

//                const uint8_t* messageTypePtr = boost::asio::buffer_cast<const uint8_t*>(buffer.data());

//                std::vector<uint8_t> oDataRead(messageTypePtr, messageTypePtr+ExpectedDataTypeSharedBond->getSTBinarySize());

//                ExpectedDataTypeSharedBond->deserialize(oDataRead);
//                ExpectedDataTypeSharedBond->doTheProcessing();

//                //#TODO - sent further
//            }
//        }
//        else
//        {
//            mExpectedDataTypes.erase(ExpectedDataTypeIterator);
//        }
//    }


//}

//void STInterface::STInterfaceClient::send(boost::asio::ip::tcp::socket & socket, const std::string& message)
//{
//    const std::string msg = message + "\n";
//    boost::asio::write( socket, boost::asio::buffer(message) );
//}


//void STInterface::STInterfaceClient::processOneLoop()
//{
//    boost::asio::ip::tcp::socket socket(mIoService);
//    mAcceptor.accept(socket);
//    read(socket);
//    send(socket, "");
//}

//void STInterface::STInterfaceClient::processContinously()
//{
//    mContinueProcessing = true;
//    while(mContinueProcessing == true)
//    {
//        processOneLoop();
//    }
//}

//void STInterface::STInterfaceClient::processContinouslyInSeparateThread()
//{
//    mThread = new boost::thread(boost::bind(&STInterface::STInterfaceClient::processContinously, this));
//}

//void STInterface::STInterfaceClient::stopProcessing()
//{
//    mContinueProcessing = false;
//}

