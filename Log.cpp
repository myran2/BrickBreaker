#include "Log.h"

bool Log::debugMode = false;
std::ofstream Log::logFile;

bool Log::init(const std::string& filename, bool debug)
{
    Log::logFile.open(filename);

    if (!logFile.is_open())
        return false;

    Log::debugMode = debug;
    return true;
}

void Log::toggleDebug()
{
    debugMode = !debugMode;
}

void Log::error(const std::string& msg)
{
    std::cout << CONSOLE_COLOR_RED << PREFIX_ERROR << msg << CONSOLE_COLOR_NONE << std::endl;
    logFile << PREFIX_ERROR << msg << std::endl;
}

void Log::warn(const std::string& msg)
{
    std::cout << CONSOLE_COLOR_YELLOW << PREFIX_WARN << msg << CONSOLE_COLOR_NONE << std::endl;
    logFile << PREFIX_WARN << msg << std::endl;
}

void Log::info(const std::string& msg)
{
    std::cout << CONSOLE_COLOR_GREEN << PREFIX_INFO << msg << CONSOLE_COLOR_NONE << std::endl;
    logFile << PREFIX_INFO << msg << std::endl;
}

void Log::debug(const std::string& msg)
{
    if (debugMode)
        std::cout << CONSOLE_COLOR_CYAN << PREFIX_DEBUG << msg << CONSOLE_COLOR_NONE << std::endl;
    
    logFile << PREFIX_DEBUG << msg << std::endl;
}
