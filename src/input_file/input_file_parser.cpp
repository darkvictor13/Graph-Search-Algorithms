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
    line.reserve(64);
    while (!_in.eof()) {
        // get the line and save in line
        std::getline(_in, line);
        if (line.empty() || line.front() == '%') {
            continue;
        }

        // TODO: pensar em um jeito de first_word e arguments não alocarem
        // memória, talvez usando string_view
        const auto first_parenthesis = line.find('(');
        const auto first_word = line.substr(0, first_parenthesis);
        const auto arguments = line.substr(
            first_parenthesis + 1,
            line.find(')', first_parenthesis + 2) - first_parenthesis - 1);

        DEBUG_LOG(arguments.c_str());
        DEBUG_LOG(first_word.c_str());

        if (first_word == "ilha_inicial") {
            graph._start_node = std::move(arguments);
        } else if (first_word == "ilha_final") {
            graph._end_node = std::move(arguments);
        } else if (first_word == "ponte") {
            const auto first_comma = arguments.find(',');
            const auto second_comma = arguments.find(',', first_comma + 1);

            const auto start_node = arguments.substr(0, first_comma);
            const auto end_node = arguments.substr(
                first_comma + 1, second_comma - first_comma - 1);
            const auto weight = std::stoi(arguments.substr(second_comma + 1));

            graph._nodes[start_node].emplace_back(end_node, weight);
        }
    }

    return graph;
}

InputFileParser::~InputFileParser() {
    DEBUG_LOG("Destrutor");
    _in.close();
}
