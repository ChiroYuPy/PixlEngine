//
// Created by adrian on 21/05/25.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <sstream>
#include <mutex>

enum class LogLevel {
    None,
    Trace,
    Debug,
    Info,
    Success,
    Warn,
    Error,
    Fatal
};

class Logger {
public:
    static void setLevel(LogLevel level);
    static LogLevel getLevel();

    class LogStream;

    static LogStream trace();
    static LogStream debug();
    static LogStream info();
    static LogStream success();
    static LogStream warn();
    static LogStream error();
    static LogStream fatal();

private:
    static const int SeparatorWidth;
    static const std::string SeparatorString;
    static LogLevel currentLevel;
    static std::mutex mtx;

    static void log(LogLevel level, const std::string &message);
    static std::string getColor(LogLevel level);
    static std::string getHeader(LogLevel level);
};

class Logger::LogStream {
public:
    LogStream(LogLevel level)
            : level(level) {}

    ~LogStream() {
        Logger::log(level, ss.str());
    }

    template <typename T>
    LogStream& operator<<(const T& val) {
        ss << val;
        return *this;
    }
private:
    LogLevel level;
    std::ostringstream ss;
};


#endif //LOGGER_H
