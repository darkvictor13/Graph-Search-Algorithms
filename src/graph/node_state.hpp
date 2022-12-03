#pragma once

enum NodeState { HAS_NONE = 0, HAS_WEIGHT, HAS_HEURISTIC, HAS_BOTH };

constexpr inline void setHasWeight(NodeState& state);

constexpr inline void setHasHeuristic(NodeState& state);