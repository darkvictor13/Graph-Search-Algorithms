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
 * @brief Pega a hora atual formatada.
 *
 * Formato: HH:MM:SS.mmm
 *
 * @param time o tempo a ser formatado.
 * @return const char* ponteiro para a string com a hora formatada.
 */
const char* getFormattedTime(
    std::chrono::high_resolution_clock::time_point time);

/**
 * @brief Pega a data atual formatada.
 *
 * Formato: DD/MM/YYYY
 *
 * @return const char* ponteiro para a string com a data formatada.
 */
const char* getFormattedDate();