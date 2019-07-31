#pragma once

#include <iostream>

const std::wstring LOG_LEVEL_STRINGS[] = {L"Debug", L"Trace", L"Info", L"Warning", L"Error",L"Fatal"};
enum LogImportanceLevel
{
    Debug = 0,
    Trace = 1,
    Info = 2,
    Warning = 3,
    Error = 4,
    Fatal = 5
};
