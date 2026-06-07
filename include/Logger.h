#pragma once

#include <mutex>   // for std::mutex
#include <string>  // for std::string

class Logger
{
private:
    std::mutex logMutex; // protects console output

public:
    void log(const std::string& message); // print message safely
};