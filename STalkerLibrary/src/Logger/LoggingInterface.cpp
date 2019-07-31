#include "LoggingInterface.h"

using namespace STalker::LogUtils;

LoggingInterface::~LoggingInterface(){}

//=======================================================================
//
void LoggingInterface::setLogImportanceLevel(const enum LogImportanceLevel& iLogLevel)
{
    mMinLogImportanceLevel=iLogLevel;
}

//=======================================================================
//
enum LogImportanceLevel LoggingInterface::minLogImportanceLevel()
{
    return mMinLogImportanceLevel;
}

//=======================================================================
//
void LoggingInterface::setEnable(const bool iEnable)
{
    mEnabled = iEnable;
}

//=======================================================================
//
bool LoggingInterface::isEnabled()
{
    return mEnabled;
}
