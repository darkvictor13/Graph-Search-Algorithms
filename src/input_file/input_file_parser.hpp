#pragma once

#include <fstream>
#include <string_view>

#include "../graph/graph.hpp"

class InputFileParser {
    private:
        /**
         * @brief O arquivo de entrada.
         */
        std::ifstream _in;

    public:
        InputFileParser(const InputFileParser&) = delete;

        /**
         * @brief Construtor padrão.
         *
         * @param path O caminho do arquivo de entrada.
         */
        InputFileParser(const std::string_view path);

        /**
         * @brief Analisa o arquivo de entrada.
         *
         * @return Graph O grafo gerado a partir do arquivo de entrada.
         */
        Graph parse();

        /**
         * @brief Destrutor padrão.
         */
        ~InputFileParser();
};