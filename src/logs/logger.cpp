#include "logger.hpp"

#include <chrono>
#include <filesystem>
#include <iostream>

#include "date_time.hpp"

const char* Logger::getLevelName(const LogLevel level) {
    // const char* const levelNames[] = {"DEBUG", "INFO", "WARNING", "ERROR",
    // "FATAL"};
    const char* const levelNames[] = {"D", "I", "W", "E", "F"};
    return levelNames[static_cast<int>(level)];
}

Logger::Logger() : _level(DEFAULT_LOG_LEVEL) {
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setLevel(const LogLevel level) {
    _level = level;
}

void Logger::doLog(const LogLevel level, const std::string_view message,
                   const std::source_location& source) {
    if (level < _level) {
        return;
    }
    std::cout << "[" << getLevelName(level) << "][" << getFormattedTime()
              << "]["
              << std::filesystem::path(source.file_name()).filename().string()
              << ':' << source.function_name() << ':' << source.line()
              << "]: " << message << '\n';
}

Logger::~Logger() {
}
