#include <iostream>
#include "TerminalLogger.h"

using namespace STalker::LogUtils;

//=======================================================================
//
void TerminalLogger::logMessage(const LogImportanceLevel& iLogLevel,const std::wstring& iMessage)
{
    if(this->isEnabled() && iLogLevel >= minLogImportanceLevel())
    {
        std::wcout << iMessage;
    }
}
