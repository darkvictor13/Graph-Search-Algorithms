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
         * @brief
         *
         * @param path
         */
        void build(const char* path);
        /**
         * @brief Pegue a instância do FileLogger.
         *
         * @return FileLogger& instância do FileLogger.
         */
        static FileLogger& getInstance();
        std::ofstream& operator<<(const std::string_view message);
        ~FileLogger();
};