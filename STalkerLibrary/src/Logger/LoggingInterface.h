#pragma once

#include <string>

#include "LoggerGlobals.h"

namespace STalker  {
namespace LogUtils  {

class LoggingInterface
{  
public:
    virtual void logMessage(const enum LogImportanceLevel& iLogLevel,const std::wstring& iMsg)=0;
    virtual void setLogImportanceLevel(const enum LogImportanceLevel& iLogLevel);
    virtual enum LogImportanceLevel minLogImportanceLevel();
    virtual void setEnable(const bool iEnable);
    virtual bool isEnabled();

    virtual ~LoggingInterface()=0;
protected:
    bool mEnabled = true;
    LogImportanceLevel mMinLogImportanceLevel=LogImportanceLevel::Debug;
};

} //namespace Logger
} //namespace STalker
