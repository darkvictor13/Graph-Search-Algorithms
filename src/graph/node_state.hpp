#pragma once

/**
 * @brief Indica o estado de um nó.
 *
 * Se ele possui um valor de peso ou heurístico.
 */
enum NodeState { HAS_NONE = 0, HAS_WEIGHT, HAS_HEURISTIC, HAS_BOTH };

/**
 * @brief Faz com que o estado indique que o nó possui um peso.
 *
 * @param state O estado atual do nó.
 */
constexpr inline void setHasWeight(NodeState& state);

/**
 * @brief Faz com que o estado indique que o nó possui uma heurística.
 *
 * @param state O estado atual do nó.
 */
constexpr inline void setHasHeuristic(NodeState& state);