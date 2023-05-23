#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <string_view>

#define log(message) Logger::shared().logMsg(message, __FILE__, __LINE__, __func__)

class Logger {
public:
    static Logger& shared() {
        static Logger instance;
        return instance;
    }

    void logMsg(std::string_view message, const char* file, int line, const char* function);

    void openLogFile(const std::string& filename);

    void closeLogFile();

private:
    std::ofstream fileStream;

    Logger();

    ~Logger();

    Logger(const Logger&) = delete;

    Logger& operator=(const Logger&) = delete;

    std::string getTimestamp();
};