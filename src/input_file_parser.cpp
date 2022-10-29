#include "input_file_parser.hpp"

#include <string>
#include <string_view>

#include "utils/log_macros.hpp"

InputFileParser::InputFileParser(const std::string_view path) {
    DEBUG_LOG("Construtor");
    _in.open(path.data());
    if (!_in.is_open()) {
        char buffer[256];
        sprintf(buffer, "Could not open file %s", path.data());
        FATAL_LOG(buffer);
        exit(EXIT_FAILURE);
    }
}

Graph InputFileParser::parse() {
    DEBUG_LOG("Analisando arquivo de entrada");

    Graph graph;
    std::string line;
    while (!_in.eof()) {
        std::getline(_in, line);
        if (line.empty() || line[0] == '%') {
            continue;
        }
    }

    return graph;
}

InputFileParser::~InputFileParser() {
    DEBUG_LOG("Destrutor");
}
