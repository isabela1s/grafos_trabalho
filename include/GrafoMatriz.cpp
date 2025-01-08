#include "GrafoMatriz.h"
#include <fstream>
#include <iostream>
#include <queue>

// Construtor
GrafoMatriz::GrafoMatriz(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada)
    : Grafo(numVertices, direcionado, verticePonderado, arestaPonderada) {
    matrizAdj.resize(numVertices, std::vector<int>(numVertices, 0)); // Inicializa matriz com 0
}

// Destrutor
GrafoMatriz::~GrafoMatriz() {}

// Adicionar vértice
void GrafoMatriz::adicionar_vertice() {
    for (auto& linha : matrizAdj) {
        linha.push_back(0); // Adiciona uma coluna de 0 para o novo vértice
    }
    matrizAdj.emplace_back(matrizAdj.size() + 1, 0); // Adiciona uma nova linha
    numVertices++;
}

// Adicionar aresta
void GrafoMatriz::adicionar_aresta(int origem, int destino, int peso) {
    matrizAdj[origem][destino] = peso;
    if (!direcionado) {
        matrizAdj[destino][origem] = peso; // Grafo não direcionado
    }
    numArestas++;
}

// Esqueleto das funções obrigatórias

bool GrafoMatriz::eh_bipartido() const {
    std::vector<int> cores(numVertices, -1); // -1 = Não colorido
    std::queue<int> fila;

    for (int i = 0; i < numVertices; ++i) {
        if (cores[i] == -1) { // Não visitado
            cores[i] = 0; // Primeira cor
            fila.push(i);

            while (!fila.empty()) {
                int vertice = fila.front();
                fila.pop();

                for (int j = 0; j < numVertices; ++j) {
                    if (matrizAdj[vertice][j] != 0) { // Aresta existe
                        if (cores[j] == -1) { // Não colorido
                            cores[j] = 1 - cores[vertice]; // Alterna cor
                            fila.push(j);
                        } else if (cores[j] == cores[vertice]) {
                            return false; // Não é bipartido
                        }
                    }
                }
            }
        }
    }
    return true; // É bipartido
}

int GrafoMatriz::n_conexo() const {
    std::vector<bool> visitados(numVertices, false);
    int componentes = 0;

    for (int i = 0; i < numVertices; ++i) {
        if (!visitados[i]) {
            componentes++;
            dfs(i, visitados); // Chama a versão de 2 parâmetros
        }
    }

    return componentes;
}
int GrafoMatriz::get_grau(int vertice) const {
    int grau = 0;
    for (int i = 0; i < numVertices; ++i) {
        if (matrizAdj[vertice][i] != 0) { // Conta as arestas conectadas
            grau++;
        }
    }
    return grau;
}


bool GrafoMatriz::possui_ponte() const {
    // Número de componentes conexos no grafo original
    int componentesOriginais = n_conexo();

    // Cria uma cópia da matriz de adjacência
    auto matrizCopia = matrizAdj;

    for (int u = 0; u < numVertices; ++u) {
        for (int v = 0; v < numVertices; ++v) {
            if (matrizCopia[u][v] != 0) { // Existe aresta (u, v)
                // Remove temporariamente a aresta (u, v)
                int pesoBackup = matrizCopia[u][v];
                matrizCopia[u][v] = 0;
                if (!direcionado) {
                    matrizCopia[v][u] = 0;
                }

                // Recalcula o número de componentes conexos com a cópia
                int novosComponentes = n_conexo();

                // Restaura a aresta (u, v)
                matrizCopia[u][v] = pesoBackup;
                if (!direcionado) {
                    matrizCopia[v][u] = pesoBackup;
                }

                // Verifica se o número de componentes aumentou
                if (novosComponentes > componentesOriginais) {
                    return true; // Encontrou uma ponte
                }
            }
        }
    }

    return false; // Nenhuma ponte encontrada
}

bool GrafoMatriz::possui_articulacao() const {
    int componentesOriginais = n_conexo();

    for (int v = 0; v < numVertices; ++v) {
        auto matrizCopia = matrizAdj;

        // Remove temporariamente o vértice v
        for (int u = 0; u < numVertices; ++u) {
            matrizCopia[v][u] = 0;
            matrizCopia[u][v] = 0;
        }

        int novosComponentes = 0;
        std::vector<bool> visitados(numVertices, false);
        for (int i = 0; i < numVertices; ++i) {
            if (!visitados[i]) {
                novosComponentes++;
                dfs(i, visitados, matrizCopia); // Chama a versão de 3 parâmetros
            }
        }

        if (novosComponentes > componentesOriginais) {
            return true; // Ponto de articulação encontrado
        }
    }

    return false; // Nenhum ponto de articulação encontrado
}
// DFS modificado para usar a cópia da matriz
void GrafoMatriz::dfs(int vertice, std::vector<bool>& visitados, const std::vector<std::vector<int>>& matriz) const {
    visitados[vertice] = true;
    for (int i = 0; i < numVertices; ++i) {
        if (matriz[vertice][i] != 0 && !visitados[i]) { // Verifica aresta e não visitado
            dfs(i, visitados, matriz); // Chamada recursiva
        }
    }
}
void GrafoMatriz::dfs(int vertice, std::vector<bool>& visitados) const {
    visitados[vertice] = true;
    for (int i = 0; i < numVertices; ++i) {
        if (matrizAdj[vertice][i] != 0 && !visitados[i]) { // Verifica aresta e não visitado
            dfs(i, visitados); // Chamada recursiva
        }
    }
}
bool GrafoMatriz::eh_completo() const {
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            // Ignora a diagonal, pois um vértice não está conectado a si mesmo
            if (i != j && matrizAdj[i][j] == 0) {
                return false; // Se alguma aresta estiver faltando, o grafo não é completo
            }
        }
    }
    return true; // O grafo é completo
}


bool GrafoMatriz::eh_arvore() const {
    return (n_conexo() == 1) && (numArestas == numVertices - 1);
}

void GrafoMatriz::carregar_grafo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return;
    }

    // Lê o número de vértices
    int numVerticesArquivo;
    arquivo >> numVerticesArquivo;

    if (numVerticesArquivo != numVertices) {
        std::cerr << "Número de vértices no arquivo não corresponde ao grafo." << std::endl;
        return;
    }

    // Lê a matriz de adjacência
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            arquivo >> matrizAdj[i][j];
            if (matrizAdj[i][j] != 0) {
                // Para grafos não direcionados, preenche também a posição inversa
                matrizAdj[j][i] = matrizAdj[i][j];
            }
        }
    }

    arquivo.close();
}

void GrafoMatriz::imprimir_grafo(const std::string& nomeArquivo) const {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        return;
    }

    arquivo << "Matriz de Adjacência:\n"; // Adiciona um título para a matriz
    for (const auto& linha : matrizAdj) {
        for (int peso : linha) {
            arquivo << peso << " ";
        }
        arquivo << "\n";
    }
    arquivo.close();
    std::cout << "Grafo salvo em " << nomeArquivo << std::endl;
}

int GrafoMatriz::get_ordem() const {
    return numVertices;
}

bool GrafoMatriz::eh_direcionado() const {
    return direcionado;
}

bool GrafoMatriz::vertice_ponderado() const {
    return verticePonderado;
}

bool GrafoMatriz::aresta_ponderada() const {
    return arestaPonderada;
}
