#include "date_time.hpp"

#include <string.h>

const char* getFormattedTime() {
    static constexpr uint8_t STR_MAX_SIZE = 32;
    static char buffer[STR_MAX_SIZE];

    const auto now = std::chrono::system_clock::now();
    const auto nowTime = std::chrono::system_clock::to_time_t(now);

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

const char* getFormattedDate() {
    // isso ta errado
    // TODO: arrumar
    return __DATE__;
}
