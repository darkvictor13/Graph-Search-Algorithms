#pragma once

#include <string>

class AdjacencyNode {
    private:
        std::string id;
        int16_t weight;

    public:
        AdjacencyNode();
        ~AdjacencyNode();
};