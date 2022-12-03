#pragma once

#include <functional>
#include <source_location>
#include <string_view>

#include "../logs/date_time.hpp"

typedef std::function<void(const char* scope_name, const char* formatted_time)>
    LogFunction;

#define DEFAULT_TIMER                                              \
    ScopedTimer __timer(                                           \
        [](const char* scope_name, const char* formatted_time) {   \
            char buffer[256];                                      \
            sprintf(buffer, "%s: %s", scope_name, formatted_time); \
            DEBUG_LOG(buffer);                                     \
        })

class ScopedTimer {
    private:
        LogFunction _log_function;
        const char* _scope_name;
        std::chrono::high_resolution_clock::time_point _start;

    public:
        ScopedTimer(LogFunction log_function,
                    const char* scope_name =
                        std::source_location::current().function_name());
        ~ScopedTimer();
};