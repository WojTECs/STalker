#include "FileLogger.h"

using namespace STalker::LogUtils;

//=======================================================================
//
FileLogger::FileLogger()//const std::experimental::filesystem::path iPath) : mLoggingDirectoryPath(iPath)
{
//    //Timestamp preparation
//    std::time_t result = std::time(nullptr);
//    std::string time(std::asctime(std::localtime(&result)));

//    //Removal of \n at the end of date string
//    time.pop_back();

//    mLoggingDirectoryPath.replace_filename("STalkerLog:" + time);
}

//=======================================================================
//
FileLogger::~FileLogger()
{}

//=======================================================================
//
void FileLogger::setLoggingDirectoryPath()//const std::experimental::filesystem::path iPath)
{
//    mLoggingDirectoryPath = iPath;

//    //Timestamp preparation
//    std::time_t result = std::time(nullptr);
//    std::string time(std::asctime(std::localtime(&result)));

//    //Removal of \n at the end of date string
//    time.pop_back();

//    mLoggingDirectoryPath.replace_filename("STalkerLog:" + time);
}

//=======================================================================
//
void FileLogger::logMessage(const enum LogImportanceLevel& iLogLevel,const std::wstring& iMessage)
{
////#TODOcm: log stream doesnt log messages with polish signs :<
//    if(this->isEnabled() && iLogLevel >= minLogImportanceLevel())
//    {
//        std::wofstream logFile;
        
//        logFile.open(mLoggingDirectoryPath, std::ios_base::app);
//        logFile << iMessage;
//    }

}


