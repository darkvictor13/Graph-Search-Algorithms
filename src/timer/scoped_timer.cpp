#include "scoped_timer.hpp"

#include <iostream>
#include <string>

using namespace std::chrono;
using namespace std::chrono_literals;

constexpr const auto one_sec = 1s;

std::string formatNanoseconds(const nanoseconds& ns) {
    return std::to_string(duration_cast<hours>(ns).count()) + ":" +
           std::to_string(duration_cast<minutes>(ns).count() % 60) + ":" +
           std::to_string(duration_cast<seconds>(ns).count() % 3600) + "." +
           std::to_string((ns.count() % 1000000000) / 1000000000.0) + "s";
}

ScopedTimer::ScopedTimer(LogFunction log_function, const char* scope_name)
    : _log_function(log_function),
      _scope_name(scope_name),
      _start(high_resolution_clock::now()) {
}

ScopedTimer::~ScopedTimer() {
    const auto end = high_resolution_clock::now();
    const auto duration = (end - _start);
    _log_function(_scope_name, formatNanoseconds(duration).c_str());
}
