#ifndef LOG_H_DEFINED
#define LOG_H_DEFINED

#include <fstream>
#include <iostream>

#define CONSOLE_COLOR_RED     "\e[1;31m"
#define CONSOLE_COLOR_YELLOW  "\e[1;33m"
#define CONSOLE_COLOR_GREEN   "\e[0;32m"
#define CONSOLE_COLOR_CYAN    "\e[1;36m"
#define CONSOLE_COLOR_NONE    "\e[0m"

#define PREFIX_ERROR  "Error: "
#define PREFIX_WARN   "Warn:  "
#define PREFIX_INFO   "Info:  "
#define PREFIX_DEBUG  "Debug: "

// static class that handles all logging-related tasks
class Log
{
public:
    // initializes the log file
    // logFile is the filename of the log file
    // if debug is true, debug messages will be printed to console
    static bool init(const std::string& filename, bool debug);
    static void toggleDebug();

    //TODO: add timestamps to logfile output

    // prints an error to console and the logfile
    static void error(const std::string& msg);
    // prints a warning to console and the logfile
    static void warn(const std::string& msg);
    // prints information to console and the logfile
    static void info(const std::string& msg);
    // prints debug info to console and the logfile
    static void debug(const std::string& msg);

private:
    static bool debugMode;
    static std::ofstream logFile;
};

#endif