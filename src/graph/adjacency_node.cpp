#include "adjacency_node.hpp"

#include "../logs/log_macros.hpp"

AdjacencyNode::AdjacencyNode() {
    DEBUG_LOG("Default constructor");
}

AdjacencyNode::AdjacencyNode(const std::string& id, int16_t weight)
    : _id(id), _weight(weight) {
    DEBUG_LOG("Construtor with parameters");
}

AdjacencyNode::AdjacencyNode(const AdjacencyNode& other)
    : _id(other._id), _weight(other._weight) {
    DEBUG_LOG("Copy constructor");
}

AdjacencyNode::AdjacencyNode(AdjacencyNode&& other)
    : _id(std::move(other._id)), _weight(other._weight) {
    DEBUG_LOG("Move constructor");
}

AdjacencyNode::~AdjacencyNode() {
    DEBUG_LOG("Destrutor");
}
