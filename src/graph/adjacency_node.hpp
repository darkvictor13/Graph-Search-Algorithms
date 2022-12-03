#pragma once

#include <string>

#include "node_state.hpp"

class AdjacencyNode {
        friend class Graph;
        friend class InputFileParser;

    private:
        std::string _id;
        int16_t _weight, _heuristic;
        NodeState _state;

    public:
        AdjacencyNode();
        AdjacencyNode(const std::string& id, int16_t value, bool is_weight);
        AdjacencyNode(const AdjacencyNode& other);
        AdjacencyNode(AdjacencyNode&& other);
        ~AdjacencyNode();
};