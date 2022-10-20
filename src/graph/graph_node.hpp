#pragma once

#include <string>

class GraphNode {
    private:
        // TODO: the id should be a string name or the index of the node in the
        // graph
        std::string id;
        int16_t weight;

    public:
        GraphNode();
        ~GraphNode();
};