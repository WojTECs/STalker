#pragma once

//#include <experimental/filesystem>
#include <fstream>

#include "../LoggingInterface.h"

namespace STalker  {
namespace LogUtils  {

class FileLogger : public LoggingInterface
{
private:

    //std::experimental::filesystem::path mLoggingDirectoryPath = " ";

    uintmax_t mLoggingFileSize = 0;
    uintmax_t mLoggingDirectorySize = 0;

public:
    FileLogger();//const std::experimental::filesystem::path iPath = "./");
    virtual ~FileLogger();

    //std::experimental::filesystem::path
    void GetLoggingDirectoryPath(){};// const {return mLoggingDirectoryPath;}
    void setLoggingDirectoryPath ();//const std::experimental::filesystem::path iPath);

    uintmax_t getLoggingFileSize() const {return mLoggingFileSize;}
    void setLoggingFileSize(const uintmax_t iSize){mLoggingFileSize = iSize;}

    uintmax_t getmLoggingDirectorySize() const {return mLoggingDirectorySize;}
    void setLoggingDirectorySize(const uintmax_t iSize){mLoggingDirectorySize = iSize;}

    void logMessage (const enum LogImportanceLevel& iLogLevel, const std::wstring& iMessage)  override ;
};

} //namespace LogUtils
} //namespace STalker

