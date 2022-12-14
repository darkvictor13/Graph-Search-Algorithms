#include "date_time.hpp"

#include <string>

static constexpr uint8_t STR_MAX_SIZE = 32;

const char* getFormattedTime() {
    return getFormattedTime(std::chrono::high_resolution_clock::now());
}

const char* getFormattedTime(
    std::chrono::high_resolution_clock::time_point time) {
    static char buffer[STR_MAX_SIZE];

    const auto nowTime = std::chrono::system_clock::to_time_t(time);
    const size_t size = std::strftime(buffer, STR_MAX_SIZE, "%H:%M:%S",
                                      std::localtime(&nowTime));
    buffer[size] = '.';
    const auto remaining =
        (time.time_since_epoch().count() % 1000000000) / 1000000000.0;
    const std::string remaining_str = std::to_string(remaining);
    if (remaining_str.size() + size + 1 < STR_MAX_SIZE) {
        strncpy(buffer + size + 1, remaining_str.data() + 2,
                remaining_str.size() - 2);
        buffer[size + 1 + remaining_str.size() - 2] = '\0';
    }
    return buffer;
}

const char* getFormattedDate() {
    static char buffer[STR_MAX_SIZE] = {0};
    if (buffer[0] == 0) {
        const auto time = std::chrono::system_clock::now();
        const auto nowTime = std::chrono::system_clock::to_time_t(time);
        std::strftime(buffer, STR_MAX_SIZE, "%d/%m/%Y",
                      std::localtime(&nowTime));
    }
    return buffer;
}