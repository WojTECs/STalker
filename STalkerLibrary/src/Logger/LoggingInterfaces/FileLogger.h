#pragma once

#include <filesystem>
#include <fstream>

#include "../LoggingInterface.h"

namespace STalker  {
namespace LogUtils  {

class FileLogger : public LoggingInterface
{
private:

    std::filesystem::path mLoggingDirectoryPath = " ";

    uintmax_t mLoggingFileSize = 0;
    uintmax_t mLoggingDirectorySize = 0;

public:
    FileLogger(const std::filesystem::path iPath = "./");
    virtual ~FileLogger();

    std::filesystem::path GetLoggingDirectoryPath() const {return mLoggingDirectoryPath;}
    void setLoggingDirectoryPath (const std::filesystem::path iPath);

    uintmax_t getLoggingFileSize() const {return mLoggingFileSize;}
    void setLoggingFileSize(const uintmax_t iSize){mLoggingFileSize = iSize;}

    uintmax_t getmLoggingDirectorySize() const {return mLoggingDirectorySize;}
    void setLoggingDirectorySize(const uintmax_t iSize){mLoggingDirectorySize = iSize;}

    void logMessage (const enum LogImportanceLevel& iLogLevel, const std::wstring& iMessage)  override ;
};

} //namespace LogUtils
} //namespace STalker

