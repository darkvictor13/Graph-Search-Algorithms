#pragma once

#include <vector>

#include "graph_node.hpp"

class Graph {
    private:
        std::vector<std::vector<GraphNode>> nodes;

    public:
        Graph();
        ~Graph();
};