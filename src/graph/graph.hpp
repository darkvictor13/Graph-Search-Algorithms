#pragma once

#include <unordered_map>
#include <vector>

#include "adjacency_node.hpp"

class Graph {
    private:
        // mapeia o nó para a lista de seus adjacentes
        std::unordered_map<std::string, std::vector<AdjacencyNode>> nodes;

    public:
        Graph();
        ~Graph();
};