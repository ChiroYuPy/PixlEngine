//
// Created by adrian on 21/05/25.
//

#include "core/Logger.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>

// Trace < Debug < Info < Success < Warn < Error < Fatal

const int Logger::SeparatorWidth = 48;
const std::string Logger::SeparatorString = std::string(SeparatorWidth, '-');
LogLevel Logger::currentLevel = LogLevel::Info;

void Logger::setLevel(const LogLevel level) {
    currentLevel = level;
}

LogLevel Logger::getLevel() {
    return currentLevel;
}

std::string Logger::getColor(const LogLevel level) {
    switch (level) {
        case LogLevel::Trace:   return "\033[1;90m"; // Gris clair
        case LogLevel::Debug:   return "\033[1;35m"; // Magenta
        case LogLevel::Info:    return "\033[1;36m"; // Cyan
        case LogLevel::Success: return "\033[1;32m"; // Vert
        case LogLevel::Warn:    return "\033[1;33m"; // Jaune
        case LogLevel::Error:   return "\033[1;31m"; // Rouge
        case LogLevel::Fatal:   return "\033[1;41m"; // Fond rouge
        default:                return "\033[0m";    // Réinitialisation
    }
}

std::string Logger::getHeader(const LogLevel level) {
    switch (level) {
        case LogLevel::Trace:   return " [TRACE] ";
        case LogLevel::Debug:   return " [DEBUG] ";
        case LogLevel::Info:    return " [INFO]  ";
        case LogLevel::Success: return " [OK]    ";
        case LogLevel::Warn:    return " [WARN]  ";
        case LogLevel::Error:   return " [ERROR] ";
        case LogLevel::Fatal:   return " [FATAL] ";
        default:                return "         ";
    }
}

std::string getTimestamp() {
    using namespace std::chrono;

    const auto now = system_clock::now();
    auto time = system_clock::to_time_t(now);
    std::tm localTime{};

    // Verify if we are on windows, so we can Bind the right time
#ifdef _WIN32
    localtime_s(&localTime, &time);
#else
    localtime_r(&time, &localTime);
#endif

    std::ostringstream oss;
    oss << "[" << std::put_time(&localTime, "%H:%M:%S") << "]"; // time format
    return oss.str();
}

void Logger::log(LogLevel level, const std::string& message) {
    if (static_cast<int>(level) < static_cast<int>(currentLevel)) return;

    std::ostream& out = (level == LogLevel::Error) ? std::cerr : std::cout;
    out << getColor(level) << getTimestamp() << getHeader(level) << message << getColor(LogLevel::None) << std::endl;
}

Logger::LogStream Logger::debug()   { return LogStream(LogLevel::Debug); }
Logger::LogStream Logger::info()    { return LogStream(LogLevel::Info); }
Logger::LogStream Logger::warn()    { return LogStream(LogLevel::Warn); }
Logger::LogStream Logger::error()   { return LogStream(LogLevel::Error); }
Logger::LogStream Logger::fatal()   { return LogStream(LogLevel::Fatal); }
Logger::LogStream Logger::trace()   { return LogStream(LogLevel::Trace); }
Logger::LogStream Logger::success() { return LogStream(LogLevel::Success); }