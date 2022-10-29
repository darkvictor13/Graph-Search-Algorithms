/**
 * @file logger.hpp
 * @brief Define a classe Logger e as macros de log
 * @version 0.1
 */
#pragma once

#include <source_location>
#include <string>
#include <string_view>

/**
 * @brief Os níveis de log da aplicação.
 */
enum LogLevel { DEBUG, INFO, WARNING, ERROR, FATAL };

/**
 * @brief Define o nível de log padrão da aplicação.
 */
constexpr LogLevel DEFAULT_LOG_LEVEL = LogLevel::DEBUG;

/**
 * @brief A classe Logger.
 *
 * Uma classe singleton que imprime mensagens de log no console.
 */
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
        /**
         * @brief Método auxiliar para obter a data e hora atual formatada.
         *
         * @return std::string a data e hora formatada.
         */
        std::string getFormattedTime();

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
                   const std::source_location& source =
                       std::source_location::current());
        /**
         * @brief Destrutor da classe Logger.
         */
        ~Logger();
};