#include "node_state.hpp"

constexpr inline void setHasWeight(NodeState& state) {
    state = static_cast<NodeState>(state | HAS_WEIGHT);
}

constexpr inline void setHasHeuristic(NodeState& state) {
    state = static_cast<NodeState>(state | HAS_HEURISTIC);
}