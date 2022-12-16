#pragma once

#include "../cxx_version_guard.h"

#include <functional>
//#include <source_location>
#include <string_view>

#include "../logs/date_time.hpp"

/**
 * @brief Define o tipo de função que pode ser usada para logar mensagens.
 */
typedef std::function<void(const char* scope_name, const char* formatted_time)>
    LogFunction;

/**
 * @brief Macro para criar um timer que imprime na tela o tempo de execução de
 * um escopo
 */
#define DEFAULT_TIMER                                              \
    ScopedTimer __timer(                                           \
        [](const char* scope_name, const char* formatted_time) {   \
            char buffer[256];                                      \
            sprintf(buffer, "%s: %s", scope_name, formatted_time); \
            DEBUG_LOG(buffer);                                     \
        }, __func__)

class ScopedTimer {
    private:
        /**
         * @brief Função que será chamada quando o timer for destruído.
         */
        LogFunction _log_function;
        /**
         * @brief Nome do escopo que está sendo medido.
         */
        const char* _scope_name;
        /**
         * @brief Momento em que o timer foi criado.
         */
        std::chrono::high_resolution_clock::time_point _start;

    public:
        /**
         * @brief Construtor da classe ScopedTimer.
         *
         * @param log_function função que será chamada quando o timer for
         * destruído, aceita função lambda.
         * @param scope_name nome do escopo que está sendo medido.
         */
        ScopedTimer(LogFunction log_function,
                    const char* scope_name);
        /**
         * @brief Destrutor da classe ScopedTimer.
         */
        ~ScopedTimer();
};