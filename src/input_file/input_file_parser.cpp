#include "input_file_parser.hpp"

#include <iostream>
#include <string>
#include <string_view>

#include "../logs/log_macros.hpp"

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
    // line.reserve(64);
    while (!_in.eof()) {
        // get the line and save in line
        std::getline(_in, line);
        if (line.empty() || line.front() == '%') {
            continue;
        }

        const auto first_parenthesis = line.find('(');
        // the first word is the beginning of the line to the first parenthesis
        const std::string_view first_word = line.substr(0, first_parenthesis);
        const auto arguments = std::move(line.substr(
            first_parenthesis + 1,
            line.find(')', first_parenthesis + 2) - first_parenthesis - 1));

        std::cout << "first_word: " << first_word << '\n';
        DEBUG_LOG(arguments.c_str());

        if (first_word == "ilha_inicial") {
            graph.setStartNode(arguments);
        } else if (first_word == "ilha_final") {
            graph.setEndNode(arguments);
        }
    }

    return graph;
}

InputFileParser::~InputFileParser() {
    DEBUG_LOG("Destrutor");
}
