#pragma once

#include <chrono>

/**
 * @brief Pega a hora atual formatada.
 *
 * Formato: HH:MM:SS.mmm
 *
 * @return const char* ponteiro para a string com a hora formatada.
 */
const char* getFormattedTime();

/**
 * @brief Pega a data atual formatada.
 *
 * @return const char* ponteiro para a string com a data formatada.
 */
const char* getFormattedDate();