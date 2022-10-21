#pragma once

#include <source_location>
#include <string>
#include <string_view>

enum class LogLevel { DEBUG, INFO, WARNING, ERROR, FATAL };

class Logger {
    private:
        LogLevel _level;
        const std::string log_file_name;

    private:
        Logger();
        const char* getLevelName(const LogLevel level);
        std::string getFormattedTime();

    public:
        static Logger& getInstance();
        void setLevel(const LogLevel level);
        void doLog(const LogLevel level, const std::string_view message,
                   const std::source_location source =
                       std::source_location::current());
        ~Logger();
};