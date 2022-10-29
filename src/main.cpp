#include <cstdlib>
#include <iostream>
#include <string_view>

#include "graph/graph.hpp"
#include "input_file_parser.hpp"
#include "utils/file_logger.hpp"
#include "utils/log_macros.hpp"

/**
 * @mainpage Documentação do projeto
 *
 * @section intro_sec Introdução
 *
 * @section uso_sec Como usar
 *  Para usar o programa, basta executar o comando:
 * @code
 * ./exec <arquivo de entrada> <arquivo com as métricas> <algoritmo>
 * @endcode
 * Todos os argumentos são opcionais. Caso não sejam passados, o programa irá
 * perguntar ao usuário.
 */

/**
 * @brief Mostra a mensagem de como utilizar o programa.
 */
void helpMessage() {
    std::cout
        << "Uso: ./exec [arguments] | [-h] | [--help]\n"
        << "[-h] [--help]: Mostra essa mensagem de ajuda\n"
        << "Argumentos:\n"
        << "\tArgumento 1: Arquivo de entrada\n"
        << "\tArgumento 2: Arquivo para guardar as métricas\n"
        << "\tArgumento 3: Algoritmo a ser executado (A -> A*, B -> BFS)\n";
}

/**
 * @brief Lê do usuário o caminho do arquivo de entrada.
 *
 * @return char* O caminho do arquivo de entrada.
 */
const char* getInputFile() {
    // TODO: Implementar
    return "input_files/exemplo_prof.txt";
}

int main(int argc, const char* const* argv) {
    if (argc > 3) {
        FATAL_LOG("Invalid number of arguments");
        helpMessage();
        return EXIT_FAILURE;
    }

    Graph graph;

    // analisando argv[1]
    std::string_view arg = argc >= 1 ? argv[1] : "";
    if (arg == "-h" || arg == "--help") {
        helpMessage();
        return EXIT_SUCCESS;
    }
    if (arg == "") {
        arg = getInputFile();
    }
    InputFileParser parser(arg);
    graph = parser.parse();

    // analisando argv[2]
    arg = argc >= 2 ? argv[2] : "";

    return EXIT_SUCCESS;
}