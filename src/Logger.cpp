#include "Logger.h"

#include <iostream> // for std::cout

void Logger::log(const std::string& message)
{
    std::lock_guard<std::mutex> lock(logMutex); // lock mutex until function ends

    std::cout << message << std::endl; // print message to console
}