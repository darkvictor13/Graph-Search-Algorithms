#include "adjacency_node.hpp"

#include "../logs/log_macros.hpp"

AdjacencyNode::AdjacencyNode()
    : _id(""), _weight(0), _heuristic(0), _state(NodeState::HAS_NONE) {
    DEBUG_LOG("Default constructor");
}

AdjacencyNode::AdjacencyNode(const std::string& id, int16_t value,
                             bool is_weight)
    : _id(id) {
    DEBUG_LOG("Construtor with parameters");
    if (is_weight) {
        _weight = value;
        _state = NodeState::HAS_WEIGHT;
    } else {
        _heuristic = value;
        _state = NodeState::HAS_HEURISTIC;
    }
}

AdjacencyNode::AdjacencyNode(const AdjacencyNode& other)
    : _id(other._id),
      _weight(other._weight),
      _heuristic(other._heuristic),
      _state(other._state) {
    DEBUG_LOG("Copy constructor");
}

AdjacencyNode::AdjacencyNode(AdjacencyNode&& other) noexcept
    : _id(std::move(other._id)),
      _weight(other._weight),
      _heuristic(other._heuristic),
      _state(other._state) {
    DEBUG_LOG("Move constructor");
}

AdjacencyNode::~AdjacencyNode() {
    DEBUG_LOG("Destrutor");
}
