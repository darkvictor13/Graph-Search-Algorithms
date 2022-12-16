#pragma once

#include "../cxx_version_guard.h"

#include "logger.hpp"

/*
#ifdef NDEBUG
    #define DEBUG_LOG(message)
    #define INFO_LOG(message)
    #define WARNING_LOG(message)
    #define ERROR_LOG(message)
    #define FATAL_LOG(message)
#else
*/
#define DEBUG_LOG(message) Logger::getInstance().doLog(LogLevel::DEBUG, message, __FILE__, __func__, __LINE__)
#define INFO_LOG(message) Logger::getInstance().doLog(LogLevel::INFO, message, __FILE__, __func__, __LINE__)
#define WARNING_LOG(message) Logger::getInstance().doLog(LogLevel::WARNING, message, __FILE__, __func__, __LINE__)
#define ERROR_LOG(message) Logger::getInstance().doLog(LogLevel::ERROR, message, __FILE__, __func__, __LINE__)
#define FATAL_LOG(message) Logger::getInstance().doLog(LogLevel::FATAL, message, __FILE__, __func__, __LINE__)
// #endif


