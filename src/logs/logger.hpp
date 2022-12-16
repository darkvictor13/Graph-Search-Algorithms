#pragma once

#include "../cxx_version_guard.h"

//#include <source_location>
#include <string>
#include <string_view>

/**
 * @brief Os níveis de log da aplicação.
 */
enum LogLevel { DEBUG, INFO, WARNING, ERROR, FATAL };

/**
 * @brief Define o nível de log padrão da aplicação.
 */
constexpr LogLevel DEFAULT_LOG_LEVEL = LogLevel::FATAL;

class Logger {
    private:
        /**
         * @brief O nível de log atual.
         */
        LogLevel _level;

    private:
        /**
         * @brief Impossibilita a construção de uma instância de Logger.
         *
         * Garantindo que a classe seja singleton.
         */
        Logger(const Logger&) = delete;
        /**
         * @brief Construtor da classe Logger.
         *
         * Método privado para garantir que a classe seja singleton.
         */
        Logger();
        /**
         * @brief Método auxiliar para obter a string a partir do nível de log.
         *
         * @param level o nível de log.
         * @return const char* a string do nível de log.
         */
        const char* getLevelName(const LogLevel level);

    public:
        /**
         * @brief Pegue a instância do Logger.
         *
         * @return Logger& instância do Logger.
         */
        static Logger& getInstance();
        /**
         * @brief Muda o nível de log para level.
         *
         * @param level o nível de log que a aplicação deve imprimir.
         */
        void setLevel(const LogLevel level);
        /**
         * @brief Imprime uma mensagem de log.
         *
         * @param level o nível de log da mensagem.
         * @param message a mensagem a ser impressa.
         * @param source a localização da mensagem (arquivo, linha, ...).
         */
        void doLog(const LogLevel level, const std::string_view message,
                   const std::string& filename, const std::string& function_name, int line);
        /**
         * @brief Destrutor da classe Logger.
         */
        ~Logger();
};
