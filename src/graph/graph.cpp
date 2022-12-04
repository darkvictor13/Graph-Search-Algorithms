#include "graph.hpp"

#include <functional>
#include <queue>
#include <unordered_map>

#include "../logs/file_logger.hpp"
#include "../logs/log_macros.hpp"
#include "../timer/scoped_timer.hpp"

enum Colors { WHITE, GRAY, BLACK };

size_t Graph::existEdge(const std::string& start_node,
                        const std::string& end_node) const noexcept {
    try {
        const auto& vet = _nodes.at(start_node);
        for (size_t i = 0; i < vet.size(); i++) {
            if (vet[i]._id == end_node) {
                return i;
            }
        }
    } catch (const std::exception& e) {
        return -1;
    }

    return -1;
}

uint8_t getIndex(const std::string& id) {
    static std::unordered_map<std::string, uint8_t> map;
    if (map.find(id) == map.end()) {
        map[id] = static_cast<uint8_t>(map.size());
    }
    return map[id];
}

std::vector<std::string> Graph::BFS() {
    DEBUG_LOG("Iniciando BFS");

    std::vector<std::string> path;

    const auto graph_size = _nodes.size();
    std::queue<std::string> queue;
    std::string predecessors[graph_size];
    Colors colors[graph_size];
    int16_t distances[graph_size];

    for (const auto& [id, _] : _nodes) {
        const auto index = getIndex(id);
        colors[index] = WHITE;
        distances[index] = -1;
    }

    {
        // Colocando valores obtidos da ilha inicial
        const auto index = getIndex(_start_node);
        colors[index] = GRAY;
        distances[index] = 0;
        queue.push(_start_node);
        path.push_back(_start_node);
    }

    while (!queue.empty()) {
        const auto& current_node = queue.front();
        for (auto& node : _nodes[current_node]) {
            const auto index = getIndex(node._id);
            if (colors[index] == WHITE) {
                colors[index] = GRAY;
                distances[index] = distances[getIndex(current_node)] + 1;
                predecessors[index] = current_node;
                queue.push(node._id);
                path.push_back(node._id);
            }
        }
        queue.pop();
        colors[getIndex(current_node)] = BLACK;
    }

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
    ScopedTimer t([](const char* scope, const char* time) {
        FileLogger::getInstance()
            << "Execução do algoritmo demorou: " << time << "\n";
    });

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
