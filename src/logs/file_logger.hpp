#pragma once

#include <fstream>
#include <string_view>

class FileLogger {
    private:
        /**
         * @brief Indica se o arquivo está pronto para ser escrito.
         */
        bool _is_ready;
        /**
         * @brief O arquivo de log.
         */
        std::ofstream _out;

    private:
        /**
         * @brief Construtor da classe FileLogger.
         *
         * Método privado para garantir que a classe seja singleton.
         */
        FileLogger();

    public:
        /**
         * @brief Inicializa a classe FileLogger.
         *
         * Tentará abrir o arquivo de log.
         *
         * @param path caminho para o arquivo de log.
         */
        void build(const char* path);
        /**
         * @brief Pegue a instância do FileLogger.
         *
         * @return FileLogger& instância do FileLogger.
         */
        static FileLogger& getInstance();
        /**
         * @brief Escreve uma mensagem no arquivo de log.
         *
         * @param message mensagem a ser escrita.
         * @return FileLogger& referência para o próprio FileLogger.
         */
        FileLogger& operator<<(const std::string_view message);
        /**
         * @brief Fecha o arquivo de log e garante que o conteúdo seja escrito.
         */
        void destroy();
        /**
         * @brief Destrutor padrão.
         */
        ~FileLogger();
};