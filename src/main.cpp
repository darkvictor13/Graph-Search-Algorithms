#include <unistd.h>

#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string_view>
#include <thread>

#include "graph/graph.hpp"
#include "input_file/input_file_parser.hpp"
#include "logs/date_time.hpp"
#include "logs/file_logger.hpp"
#include "logs/log_macros.hpp"
#include "timer/scoped_timer.hpp"

/**
 * @mainpage Documentação do projeto
 *
 * Todas as especificações do projeto estão no relatório técnico em docs/relat/main.pdf
 */

/**
 * @brief Mostra a mensagem de como utilizar o programa.
 */
void helpMessage() {
    std::cout << "\nUso: ./exec [argumentos] | [-h] | [--help]\n\n"
              << "Argumentos:\n"
              << "\tArgumento 1: Arquivo de entrada\n"
              << "\tArgumento 2: Arquivo para guardar as métricas\n"
              << "\tArgumento 3: Algoritmo a ser executado (A -> A*, B -> BFS, "
                 "D -> DFS)\n"
              << "[-h] [--help]: Mostra essa mensagem de ajuda\n";
}

/**
 * @brief Lê do usuário a resposta para a pergunta passada como parâmetro.
 *
 * @param question A pergunta a ser feita ao usuário.
 * @return true Se a resposta for sim.
 * @return false Se a resposta for não.
 */
bool getResponse(const char* question) {
    char response;
    auto available = std::cin.rdbuf()->in_avail();
    if (available > 0) {
        std::cin.ignore(available);
    }

    std::cout << question << " (S/n): ";
    std::cin.get(response);
    available = std::cin.rdbuf()->in_avail();
    if (available > 0) {
        std::cin.ignore(available);
    }
    return std::tolower(response) != 'n';
}

std::string getInputFile() {
    std::string input_file = "input_files/exemplo_prof.txt";
    std::cout << "Arquivo de entrada padrão: " << input_file << '\n';
    if (getResponse("Deseja usar o arquivo de entrada padrão?") == false) {
        std::cout << "Digite o caminho do arquivo de entrada: ";
        std::cin >> input_file;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return input_file;
}

bool getMetricsFile(std::string& metrics_file) {
    if (getResponse("Deseja salvar as métricas em um arquivo?") == false) {
        return false;
    }

    std::string temp_file_path;
    std::cout << "Digite o caminho do arquivo: ";
    std::cin >> temp_file_path;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (std::filesystem::exists(temp_file_path)) {
        if (getResponse("O arquivo já existe. Deseja sobrescrevê-lo?") ==
            false) {
            return false;
        }
    }
    const auto& folder_path =
        std::filesystem::path(temp_file_path).parent_path();
    if (std::filesystem::exists(folder_path) || folder_path.empty()) {
        metrics_file = temp_file_path;
        return true;
    } else {
        if (getResponse("O caminho não existe. Deseja criar as pastas?") ==
            false) {
            return false;
        }
        std::filesystem::create_directories(folder_path);
        metrics_file = temp_file_path;
        return true;
    }
}

// TODO: Separar em funções a analise de cada um dos argv
// TODO: retirar variáveis que são temporárias para funções como o parser e ret
int main(int argc, const char* const* argv) {
    DEFAULT_TIMER;
    if (argc > 4) {
        FATAL_LOG("Numero de argumentos invalido");
        helpMessage();
        return EXIT_FAILURE;
    }

    bool ret;

    // analisando argv[1]
    std::string_view arg = argc > 1 ? argv[1] : "";
    if (arg == "-h" || arg == "--help") {
        helpMessage();
        return EXIT_SUCCESS;
    }

    InputFileParser parser(arg.empty() ? getInputFile() : arg);
    Graph graph(std::move(parser.parse()));

    // analisando argv[2]
    auto& file_logger = FileLogger::getInstance();
    if (argc > 2) {
        file_logger.build(argv[2]);
    } else {
        std::string arg;
        ret = getMetricsFile(arg);
        if (ret) {
            file_logger.build(arg.c_str());
        }
    }
    file_logger << "Arquivo de entrada: " << arg << "\n"
                << "Data: " << getFormattedDate() << "\n"
                << "Hora: " << getFormattedTime() << "\n";

    // analisando argv[3]
    arg = argc > 3 ? argv[3] : "";
    char algorithm;
    if (arg.empty() || arg.size() != 1) {
        std::cout << "Digite o algoritmo a ser executado (A -> A*, B -> BFS, D "
                     "-> DFS): ";
        std::cin.get(algorithm);
    } else {
        algorithm = arg[0];
    }
    algorithm = toupper(algorithm);
    if (!graph.isValidAlgorithm(algorithm)) {
        FATAL_LOG("Algoritmo invalido");
        return EXIT_FAILURE;
    }
    graph.setAlgorithm(algorithm);
    const auto& path = graph.runAlgorithm();

    file_logger << "Caminho:";
    if (path.empty()) {
        file_logger << " Nao existe\n";
    } else {
        for (const auto& node : path) {
            file_logger << " " << node;
        }
        file_logger << "\n";
    }

    return EXIT_SUCCESS;
}
