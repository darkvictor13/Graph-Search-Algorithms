#include "node_state.hpp"

void setHasWeight(NodeState& state) {
    state = static_cast<NodeState>(state | HAS_WEIGHT);
}

void setHasHeuristic(NodeState& state) {
    state = static_cast<NodeState>(state | HAS_HEURISTIC);
}

bool hasWeight(const NodeState& state) {
    return state & HAS_WEIGHT == 0b1;
}

bool hasHeuristic(const NodeState& state) {
    return state & HAS_HEURISTIC == 0b10;
}