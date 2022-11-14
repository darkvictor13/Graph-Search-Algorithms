#pragma once

#include <string>

class AdjacencyNode {
    private:
        std::string _id;
        int16_t _weight;

    public:
        AdjacencyNode();
        AdjacencyNode(const std::string& id, int16_t weight);
        AdjacencyNode(const AdjacencyNode& other);
        AdjacencyNode(AdjacencyNode&& other);
        ~AdjacencyNode();
};