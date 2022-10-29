#include "file_logger.hpp"

#include "log_macros.hpp"

FileLogger::FileLogger() : _is_ready(false), _out() {
}

void FileLogger::build(const char* path) {
    _out.open(path);
    if (_out.is_open()) {
        _is_ready = true;
    } else {
        char buffer[256];
        sprintf(buffer, "Error opening file %s", path);
        ERROR_LOG(buffer);
    }
}

FileLogger& FileLogger::getInstance() {
    static FileLogger instance;
    return instance;
}

std::ofstream& FileLogger::operator<<(const std::string_view message) {
    if (_is_ready) {
        _out << message;
    }
    return _out;
}

FileLogger::~FileLogger() {
    _out.close();
}
