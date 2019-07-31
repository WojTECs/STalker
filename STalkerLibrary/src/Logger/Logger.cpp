#include "Logger.h"
#include "LoggingInterfaces/TerminalLogger.h"

#include <ctime>
#include <iomanip>
#include <codecvt>
#include <string>

using namespace STalker;

std::list<std::weak_ptr<STalker::LogUtils::LoggingInterface>> Logger::mLoggingInterfaces;

//=======================================================================
//
void Logger::addLogger(const std::shared_ptr<STalker::LogUtils::LoggingInterface>& iLoggingInterface)
{
    mLoggingInterfaces.push_back(iLoggingInterface);
}

//=======================================================================
//
void Logger::logMessage(const LogImportanceLevel& iLogLevel, const std::wstring& iMessage)
{
    //Timestamp preparation
    std::time_t result = std::time(nullptr);
    std::string time(std::asctime(std::localtime(&result)));

    //Removal of \n at the end of date string
    time.pop_back();

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;

    //Log message construction
    std::wstring message = conv.from_bytes(time) + L" " + LOG_LEVEL_STRINGS[iLogLevel] + L":" + iMessage + L"\n";

    for (auto interfaceIterator = mLoggingInterfaces.begin(); interfaceIterator != mLoggingInterfaces.end(); interfaceIterator++)
    {
        //Checkup whether reference still exists
        std::shared_ptr<STalker::LogUtils::LoggingInterface> loggingInterfaceSharedBond;
        loggingInterfaceSharedBond = interfaceIterator->lock();

        if(loggingInterfaceSharedBond)
        {
            loggingInterfaceSharedBond->logMessage(iLogLevel,message);
        }
        else
        {
           mLoggingInterfaces.erase(interfaceIterator);
        }
    }
}

//=======================================================================
//
void Logger::clear()
{
   mLoggingInterfaces.clear();
}
