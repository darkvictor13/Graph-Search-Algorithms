#pragma once

#include <string>

#include "node_state.hpp"

class AdjacencyNode {
        friend class Graph;
        friend class InputFileParser;

    private:
        /**
         * @brief O identificador do nó que é o destino da aresta.
         */
        std::string _id;
        /**
         * @brief O peso da aresta.
         */
        int16_t _weight;
        /**
         * @brief O Valor em linha reta do nó origem.
         */
        int16_t _heuristic;
        /**
         * @brief O estado do nó.
         *
         * Se possui um valor de peso ou heurístico.
         */
        NodeState _state;

    public:
        AdjacencyNode();
        AdjacencyNode(const std::string& id, int16_t value, bool is_weight);
        AdjacencyNode(const AdjacencyNode& other);
        AdjacencyNode(AdjacencyNode&& other);
        ~AdjacencyNode();
};