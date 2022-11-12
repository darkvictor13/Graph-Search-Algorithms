#include "date_time.hpp"

#include <string.h>

static constexpr uint8_t STR_MAX_SIZE = 32;

const char* getFormattedTime() {
    return getFormattedTime(std::chrono::high_resolution_clock::now());
}

const char* getFormattedTime(
    std::chrono::high_resolution_clock::time_point time) {
    static char buffer[STR_MAX_SIZE];

    // const auto time = std::chrono::system_clock::now();
    // const auto nowTime = std::chrono::system_clock::to_time_t(time);
    const auto nowTime = std::chrono::system_clock::to_time_t(time);

    const size_t size = std::strftime(buffer, STR_MAX_SIZE, "%H:%M:%S",
                                      std::localtime(&nowTime));
    buffer[size] = '.';
    const auto remaining =
        (time.time_since_epoch() % std::chrono::seconds(1)).count();
    const std::string remaining_str = std::to_string(remaining);
    if (remaining_str.size() + size + 1 < STR_MAX_SIZE) {
        strncpy(buffer + size + 1, remaining_str.data(), remaining_str.size());
        buffer[size + 1 + remaining_str.size()] = '\0';
    }
    return buffer;
}

const char* getFormattedDate() {
    // isso ta errado
    // TODO: arrumar
    return __DATE__;
}