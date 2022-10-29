#include "logger.hpp"

#include <string.h>

#include <chrono>
#include <filesystem>
#include <iostream>

const char* Logger::getLevelName(const LogLevel level) {
    // const char* const levelNames[] = {"DEBUG", "INFO", "WARNING", "ERROR",
    // "FATAL"};
    const char* const levelNames[] = {"D", "I", "W", "E", "F"};
    return levelNames[static_cast<int>(level)];
}

Logger::Logger() : _level(DEFAULT_LOG_LEVEL) {
}

// TODO usar std::format
std::string Logger::getFormattedTime() {
    static constexpr uint8_t STR_MAX_SIZE = 32;
    const auto now = std::chrono::system_clock::now();
    const auto nowTime = std::chrono::system_clock::to_time_t(now);

    char buffer[STR_MAX_SIZE];

    const size_t size = std::strftime(buffer, STR_MAX_SIZE, "%H:%M:%S",
                                      std::localtime(&nowTime));
    buffer[size] = '.';
    const auto remaining =
        (now.time_since_epoch() % std::chrono::seconds(1)).count();
    const std::string remaining_str = std::to_string(remaining);
    if (remaining_str.size() + size + 1 < STR_MAX_SIZE) {
        strncpy(buffer + size + 1, remaining_str.data(), remaining_str.size());
        buffer[size + 1 + remaining_str.size()] = '\0';
    }
    return buffer;
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
