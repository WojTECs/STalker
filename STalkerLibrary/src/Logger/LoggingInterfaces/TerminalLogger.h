#pragma once

#include "../LoggingInterface.h"

namespace STalker  {
namespace LogUtils  {

class TerminalLogger : public LoggingInterface
{
private:
public:
    void logMessage(const enum LogImportanceLevel& iLogLevel, const std::wstring& iMessage) override;
};

} //namespace Logger
} //namespace STalker
