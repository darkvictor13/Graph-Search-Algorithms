#include "graph.hpp"

#include <functional>
#include <queue>
#include <unordered_map>

#include "../graph/node_state.hpp"
#include "../logs/file_logger.hpp"
#include "../logs/log_macros.hpp"
#include "../timer/scoped_timer.hpp"

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

std::vector<std::string> Graph::getPath(const std::string predecessors[]) {
    std::vector<std::string> path;

    std::string current_node = _end_node;
    while (current_node != _start_node) {
        const auto& predecessor = predecessors[getIndex(current_node)];
        if (predecessor.empty()) {
            path.clear();
            return path;
        }
        path.push_back(std::move(current_node));
        current_node = predecessor;
    }
    path.push_back(_start_node);
    return path;
}

bool Graph::dfsVisit(const std::string& actual, const std::string& final,
                     Colors colors[], std::string predecessors[]) {
    if (actual == final) {
        INFO_LOG("Nó final encontrado");
        return true;
    }

    char print_buffer[64];
    sprintf(print_buffer, "Visitando nó %s", actual.c_str());
    INFO_LOG(print_buffer);
    const auto index_id = getIndex(actual);
    colors[index_id] = GRAY;
    for (const auto& node : _nodes.at(actual)) {
        if (!hasWeight(node._state)) {
            continue;
        }
        const auto index_node = getIndex(node._id);
        if (colors[index_node] == WHITE) {
            predecessors[index_node] = actual;
            const auto ret = dfsVisit(node._id, final, colors, predecessors);
            if (ret) {
                return true;
            }
        }
    }
    colors[index_id] = BLACK;
    return false;
}

std::vector<std::string> Graph::DFS() {
    INFO_LOG("Iniciando DFS");

    const auto graph_size = _nodes.size();
    Colors colors[graph_size];
    std::string predecessors[graph_size];

    for (const auto& [id, _] : _nodes) {
        colors[getIndex(id)] = WHITE;
    }

    dfsVisit(_start_node, _end_node, colors, predecessors);
    /*
    for (const auto& [id, _] : _nodes) {
        if (colors[getIndex(id)] == WHITE) {
            dfs_visit(id, _end_node);
        }
    }
    */

    auto&& path = getPath(predecessors);

    INFO_LOG("Finalizando DFS");
    return path;
}

std::vector<std::string> Graph::BFS() {
    INFO_LOG("Iniciando BFS");
    char print_buffer[64];

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
    }

    while (!queue.empty()) {
        sprintf(print_buffer, "Tamanho da fila: %zu", queue.size());
        INFO_LOG(print_buffer);

        const auto& current_node = queue.front();
        sprintf(print_buffer, "Analisando nó: %s", current_node.c_str());
        INFO_LOG(print_buffer);
        for (auto& node : _nodes[current_node]) {
            if (!hasWeight(node._state)) {
                continue;
            }
            const auto index = getIndex(node._id);
            if (colors[index] == WHITE) {
                colors[index] = GRAY;
                distances[index] = distances[getIndex(current_node)] + 1;
                predecessors[index] = current_node;
                queue.push(node._id);
            }
        }
        queue.pop();
        colors[getIndex(current_node)] = BLACK;
    }

    auto&& path = getPath(predecessors);

    INFO_LOG("Finalizando BFS");
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
    return algorithm == static_cast<char>(Algorithms::ALGORITHM_A_STAR) ||
           algorithm == static_cast<char>(Algorithms::ALGORITHM_BFS) ||
           algorithm == static_cast<char>(Algorithms::ALGORITHM_DFS);
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
    if (_algorithm == Algorithms::ALGORITHM_DFS) {
        return DFS();
    }
    ERROR_LOG("Algoritmo invalido");
    return {};
}

Graph::~Graph() {
    DEBUG_LOG("Destrutor");
}
