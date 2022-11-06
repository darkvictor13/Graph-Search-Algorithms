#include "graph.hpp"

#include <functional>
#include <unordered_map>

#include "../logs/log_macros.hpp"

std::vector<std::string> Graph::BFS() {
    DEBUG_LOG("Iniciando BFS");
    std::vector<std::string> path;

    return path;
}

std::vector<std::string> Graph::AStar() {
    DEBUG_LOG("Iniciando A*");
    std::vector<std::string> path;

    return path;
}

Graph::Graph() noexcept
    : _nodes(),
      _start_node(),
      _end_node(),
      _algorithm(Algorithms::ALGORITHM_INVALID) {
    DEBUG_LOG("Construtor");
}

Graph::Graph(const Graph& other) noexcept
    : _nodes(other._nodes),
      _start_node(other._start_node),
      _end_node(other._end_node),
      _algorithm(other._algorithm) {
    DEBUG_LOG("Copy constructor");
}

Graph::Graph(Graph&& other) noexcept
    : _nodes(std::move(other._nodes)),
      _start_node(std::move(other._start_node)),
      _end_node(std::move(other._end_node)),
      _algorithm(other._algorithm) {
    DEBUG_LOG("Move constructor");
}

void Graph::setStartNode(const std::string& start_node) {
    _start_node = start_node;
}

void Graph::setEndNode(const std::string& end_node) {
    _end_node = end_node;
}

bool Graph::isValidAlgorithm(const char algorithm) const {
    return algorithm >= static_cast<char>(Algorithms::ALGORITHM_A_STAR) &&
           algorithm < static_cast<char>(Algorithms::ALGORITHM_INVALID);
}

void Graph::setAlgorithm(const char algorithm) {
    if (isValidAlgorithm(algorithm)) {
        setAlgorithm(static_cast<Algorithms>(algorithm));
    } else {
        ERROR_LOG("Algoritmo invalido");
    }
}

void Graph::setAlgorithm(const Algorithms algorithm) {
    _algorithm = algorithm;
}

std::vector<std::string> Graph::runAlgorithm() {
    if (_algorithm == Algorithms::ALGORITHM_A_STAR) {
        return AStar();
    }
    if (_algorithm == Algorithms::ALGORITHM_BFS) {
        return BFS();
    }
    ERROR_LOG("Algoritmo invalido");
    return {};
}

Graph::~Graph() {
    DEBUG_LOG("Destrutor");
}
