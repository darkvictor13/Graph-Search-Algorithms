#pragma once

#include <string>

class AdjacencyNode {
    private:
        std::string _id;
        int16_t _weight;

    public:
        AdjacencyNode();
        ~AdjacencyNode();
};