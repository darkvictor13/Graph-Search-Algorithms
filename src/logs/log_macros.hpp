#pragma once

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
#define DEBUG_LOG(message) Logger::getInstance().doLog(LogLevel::DEBUG, message)
#define INFO_LOG(message) Logger::getInstance().doLog(LogLevel::INFO, message)
#define WARNING_LOG(message) \
    Logger::getInstance().doLog(LogLevel::WARNING, message)
#define ERROR_LOG(message) Logger::getInstance().doLog(LogLevel::ERROR, message)
#define FATAL_LOG(message) Logger::getInstance().doLog(LogLevel::FATAL, message)
// #endif