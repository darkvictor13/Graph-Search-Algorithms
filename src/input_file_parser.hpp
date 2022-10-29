#pragma once

#include <fstream>
#include <string_view>

#include "graph/graph.hpp"

class InputFileParser {
    private:
        /**
         * @brief O arquivo de entrada.
         */
        std::ifstream _in;

    public:
        InputFileParser(const InputFileParser&) = delete;

        InputFileParser(const std::string_view path);
        Graph parse();
        ~InputFileParser();
};