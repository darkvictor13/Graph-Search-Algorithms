#pragma once

#include <unordered_map>
#include <vector>

#include "adjacency_node.hpp"

/**
 * @brief Algoritmos de busca que podem ser utilizados pelo grafo.
 */
enum class Algorithms : char {
    ALGORITHM_A_STAR = 'A',
    ALGORITHM_BFS,
    ALGORITHM_INVALID,
    ALGORITHM_DFS
};

enum Colors { WHITE, GRAY, BLACK };

class Graph {
        friend class InputFileParser;

    private:
        /**
         * @brief Nós do grafo, mapeados pelo nome do nó a sua lista de
         * adjacência.
         */
        std::unordered_map<std::string, std::vector<AdjacencyNode>> _nodes;

        /**
         * @brief nó inicial utilizado no algoritmo
         */
        std::string _start_node;
        /**
         * @brief nó final utilizado no algoritmo
         */
        std::string _end_node;
        /**
         * @brief algoritmo a ser executado
         */
        Algorithms _algorithm;

    private:
        bool dfsVisit(const std::string& actual, const std::string& final,
                      Colors colors[], std::string predecessors[]);
        /**
         * @brief Executa o algoritmo de busca em profundidade.
         *
         * @return std::vector<std::string> Lista de nós que formam o caminho
         */
        std::vector<std::string> DFS();
        /**
         * @brief Executa o algoritmo de busca em largura.
         *
         * TODO: Colocar mais informações sobre o algoritmo.
         *
         * @return std::vector<std::string> Lista de nós que formam o caminho
         */
        std::vector<std::string> BFS();
        /**
         * @brief Executa o algoritmo de busca A*.
         *
         * TODO: Colocar mais informações sobre o algoritmo.
         *
         * @return std::vector<std::string> Lista de nós que formam o caminho
         */
        std::vector<std::string> AStar();

        std::vector<std::string> getPath(const std::string predecessors[]);

    public:
        /**
         * @brief Construtor padrão.
         */
        Graph() noexcept;
        Graph(const Graph& other) noexcept;
        Graph(Graph&& other) noexcept;

        /**
         * @brief Informa caso exista um caminho entre o nó inicial e o nó
         * final.
         *
         * Somente verifica na direção inicial -> final, e não na direção final
         * -> inicial.
         *
         * @param start_node Nó inicial.
         * @param end_node Nó final.
         * @return size_t índice da aresta que conecta os dois nós na lista de
         * adjacência do nó inicial, ou -1 caso não exista.
         */
        size_t existEdge(const std::string& start_node,
                         const std::string& end_node) const noexcept;

        /**
         * @brief Verifica se o caractere passado é um algoritmo válido.
         *
         * @param algorithm caractere a ser verificado.
         * @return true se estiver entre os algoritmos válidos.
         * @return false caso contrário.
         */
        bool isValidAlgorithm(const char algorithm) const;

        /**
         * @brief Atualiza o algoritmo a ser executado.
         *
         * @param algorithm o novo algoritmo.
         */
        void setAlgorithm(const char algorithm);
        /**
         * @brief Atualiza o algoritmo a ser executado.
         *
         * @param algorithm o novo algoritmo.
         */
        void setAlgorithm(const Algorithms algorithm);

        /**
         * @brief Executa um algoritmo de busca no grafo.
         *
         * Algoritmo correspondente ao valor de _algorithm.
         *
         * @return std::vector<std::string> Lista de nós que formam o caminho
         */
        std::vector<std::string> runAlgorithm();

        /**
         * @brief Destrutor padrão.
         */
        ~Graph();
};