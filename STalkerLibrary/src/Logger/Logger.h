#pragma once

#include <string>
#include <list>
#include <memory>

#include "LoggingInterface.h"
#include "LoggerGlobals.h"

namespace STalker  {

class Logger
{
private:
public:
    static std::list<std::weak_ptr<STalker::LogUtils::LoggingInterface>> mLoggingInterfaces;

    //Adds >>REFERENCE<< for the object in the internal list of logging interfaces.
    static void addLogger(const std::shared_ptr<STalker::LogUtils::LoggingInterface>& iLoggingInterface);

    //Necessary to call to empty the list of logging interfaces. Not calling may result in SIGABRT!.
    static void clear();

    //Logs given message using every enlisted interface. If the interface is externally deleted, then is removed from the internal interface list
    static void logMessage(const LogImportanceLevel& iLogLevel,const std::wstring& iMsg);
};


} //namespace STalker
