#include "input_file_parser.hpp"

#include <iostream>
#include <string>
#include <string_view>

#include "../logs/log_macros.hpp"
#include "../timer/scoped_timer.hpp"

std::tuple<std::string, std::string, int16_t> parseArguments(
    const std::string &arguments) {
    const auto first_comma = arguments.find(',');
    const auto second_comma = arguments.find(',', first_comma + 1);

    return std::make_tuple(
        arguments.substr(0, first_comma),
        arguments.substr(first_comma + 1, second_comma - first_comma - 1),
        static_cast<int16_t>(std::stoi(arguments.substr(second_comma + 1))));
}

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
    DEFAULT_TIMER;
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
            auto &&[start_node, end_node, weight] = parseArguments(arguments);
            auto index = graph.existEdge(start_node, end_node);
            if (index == -1) {
                graph._nodes[start_node].emplace_back(end_node, weight, true);
                graph._nodes[end_node].emplace_back(start_node, weight, true);
            } else {
                graph._nodes[start_node][index]._weight = weight;
                graph._nodes[start_node][index]._state = NodeState::HAS_BOTH;

                index = graph.existEdge(end_node, start_node);
                graph._nodes[end_node][index]._weight = weight;
                graph._nodes[end_node][index]._state = NodeState::HAS_BOTH;
            }
        } else if (first_word == "h") {
            auto &&[start_node, end_node, h] = parseArguments(arguments);
            auto index = graph.existEdge(start_node, end_node);
            if (index == -1) {
                graph._nodes[start_node].emplace_back(end_node, h, false);
                graph._nodes[end_node].emplace_back(start_node, h, false);
            } else {
                graph._nodes[start_node][index]._heuristic = h;
                graph._nodes[start_node][index]._state = NodeState::HAS_BOTH;

                index = graph.existEdge(end_node, start_node);
                graph._nodes[end_node][index]._heuristic = h;
                graph._nodes[end_node][index]._state = NodeState::HAS_BOTH;
            }
        } else {
            FATAL_LOG("File has invalid syntax");
            exit(EXIT_FAILURE);
        }
    }

    return graph;
}

InputFileParser::~InputFileParser() {
    DEBUG_LOG("Destrutor");
    _in.close();
}
