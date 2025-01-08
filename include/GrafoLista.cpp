#include "GrafoLista.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>

using namespace std;

GrafoLista::GrafoLista(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada)
    : Grafo(numVertices, direcionado, verticePonderado, arestaPonderada) {}

GrafoLista::~GrafoLista() {
    // Libera a memória alocada para os vértices e arestas
    for (auto& [id, vertice] : listaAdj) {
        Aresta* atual = vertice->arestas;
        while (atual) {
            Aresta* temp = atual;
            atual = atual->prox;
            delete temp;
        }
        delete vertice;
    }
    listaAdj.clear();
}

void GrafoLista::adicionar_vertice(int id) {
    if (listaAdj.find(id) == listaAdj.end()) {
        listaAdj[id] = new Vertice(id);
        numVertices++;
    }
}

void GrafoLista::adicionar_aresta(int origem, int destino, int peso) {
    if (listaAdj.find(origem) == listaAdj.end()) {
        adicionar_vertice(origem);
    }
    if (listaAdj.find(destino) == listaAdj.end()) {
        adicionar_vertice(destino);
    }

    // Agora, adicione as arestas corretamente com o destino e o peso
    listaAdj[origem]->adicionar_aresta(destino, peso); // Passa os dois parâmetros
    if (!direcionado) {
        listaAdj[destino]->adicionar_aresta(origem, peso); // Passa os dois parâmetros
    }

    numArestas++;
}

int GrafoLista::n_conexo() const {
    unordered_map<int, bool> visitados;
    for (const auto& [id, _] : listaAdj) {
        visitados[id] = false;
    }

    int componentes = 0;
    for (const auto& [id, _] : listaAdj) {
        if (!visitados[id]) {
            dfs(id, visitados);
            componentes++;
        }
    }
    return componentes;
}

void GrafoLista::imprimir_grafo(const std::string& nomeArquivo) const {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        return;
    }

    // Itera sobre todos os vértices
    for (const auto& pair : listaAdj) {
        int vertice = pair.first;
        arquivo << "Vértice " << vertice << ": ";

        Aresta* aresta = listaAdj.at(vertice)->arestas;
        bool primeiraAresta = true;

        // Verifica as conexões de cada vértice
        while (aresta != nullptr) {
            // Evita imprimir a aresta duas vezes se o grafo for não direcionado
            if (aresta->destino > vertice || direcionado) {
                if (!primeiraAresta) {
                    arquivo << " "; // Adiciona espaço entre os destinos
                }

                arquivo << aresta->destino;

                if (aresta->peso != -1) {  // Se houver peso
                    arquivo << " (peso " << aresta->peso << ")";
                }

                primeiraAresta = false;
            }

            aresta = aresta->prox;
        }
        arquivo << std::endl;
    }

    arquivo.close();
    std::cout << "Grafo salvo em " << nomeArquivo << std::endl;
}

bool GrafoLista::eh_completo() const {
    // Implementação básica para teste
    return false;
}

bool GrafoLista::eh_arvore() const {
    // Implementação básica para teste
    return false;
}
#include "GrafoLista.h"
#include <fstream>
#include <iostream>

// Implementação básica para `get_grau`
int GrafoLista::get_grau(int vertice) const {
    if (listaAdj.find(vertice) == listaAdj.end()) {
        return 0; // Se o vértice não existe, o grau é 0
    }

    int grau = 0;
    Aresta* atual = listaAdj.at(vertice)->arestas;
    while (atual) {
        grau++;
        atual = atual->prox;
    }
    return grau;
}

// Implementação básica para `carregar_grafo`
void GrafoLista::carregar_grafo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
        return;
    }

    int origem, destino;
    while (arquivo >> origem >> destino) {
        adicionar_aresta(origem, destino);
    }

    arquivo.close();
}

bool GrafoLista::possui_articulacao() const {
    // Implementação corrigida
    int componentesOriginais = n_conexo();
    for (auto it = listaAdj.begin(); it != listaAdj.end(); ++it) {
        int id = it->first;

        // Crie uma cópia da lista de adjacências
        auto listaAdjCopia = listaAdj;
        listaAdjCopia.erase(id);

        // Recalcule os componentes conexos
        if (n_conexo() > componentesOriginais) {
            return true; // O grafo possui articulação
        }
    }
    return false; // Nenhum vértice é articulação
}

bool GrafoLista::possui_ponte() const {
    int componentesOriginais = n_conexo();

    for (const auto& pair : listaAdj) {
        int id = pair.first;
        Vertice* vertice = pair.second;

        Aresta* aresta = vertice->arestas;
        while (aresta) {
            // Crie uma cópia da lista de adjacências
            auto listaAdjCopia = listaAdj;

            // Remova temporariamente a aresta
            listaAdjCopia[id]->arestas = listaAdjCopia[id]->arestas->prox;

            // Recalcule os componentes conexos
            if (n_conexo() > componentesOriginais) {
                return true; // O grafo possui ponte
            }

            // Continue verificando
            aresta = aresta->prox;
        }
    }
    return false; // Nenhuma aresta é ponte
}

bool GrafoLista::eh_bipartido() const {
    std::unordered_map<int, int> cores;
    for (const auto& pair : listaAdj) {
        cores[pair.first] = -1; // Não colorido
    }

    for (const auto& pair : listaAdj) {
        int id = pair.first;
        if (cores[id] == -1) {
            // BFS para verificar bipartição
            std::queue<int> fila;
            fila.push(id);
            cores[id] = 0;

            while (!fila.empty()) {
                int vertice = fila.front();
                fila.pop();

                for (Aresta* aresta = listaAdj.at(vertice)->arestas; aresta; aresta = aresta->prox) {
                    int destino = aresta->destino;

                    if (cores[destino] == -1) {
                        cores[destino] = 1 - cores[vertice];
                        fila.push(destino);
                    } else if (cores[destino] == cores[vertice]) {
                        return false; // Não é bipartido
                    }
                }
            }
        }
    }

    return true; // É bipartido
}

void GrafoLista::dfs(int id, std::unordered_map<int, bool>& visitados) const {
    visitados[id] = true; // Marca o vértice como visitado
    Aresta* aresta = listaAdj.at(id)->arestas;
    while (aresta != nullptr) {
        if (!visitados[aresta->destino]) {
            dfs(aresta->destino, visitados); // Chama recursivamente para o próximo vértice
        }
        aresta = aresta->prox;
    }
}

void GrafoLista::dfs_articulacao(int id, int parent, std::unordered_map<int, int>& discovery,
                                  std::unordered_map<int, int>& low, std::unordered_map<int, bool>& visitados,
                                  int& time, bool& temArticulacao) const {
    visitados[id] = true;
    discovery[id] = low[id] = ++time;

    int filhos = 0;
    Aresta* aresta = listaAdj.at(id)->arestas;
    while (aresta != nullptr) {
        int vizinho = aresta->destino;
        if (!visitados[vizinho]) {
            filhos++;
            dfs_articulacao(vizinho, id, discovery, low, visitados, time, temArticulacao);

            // Verifica se o vizinho é um ponto de articulação
            low[id] = std::min(low[id], low[vizinho]);
            if (parent == -1 && filhos > 1) {
                temArticulacao = true;
            }
            if (parent != -1 && low[vizinho] >= discovery[id]) {
                temArticulacao = true;
            }
        } else if (vizinho != parent) {
            low[id] = std::min(low[id], discovery[vizinho]);
        }
        aresta = aresta->prox;
    }
}

void GrafoLista::dfs_ponte(int id, int parent, std::unordered_map<int, int>& discovery,
                           std::unordered_map<int, int>& low, std::unordered_map<int, bool>& visitados,
                           int& time, bool& temPonte) const {
    visitados[id] = true;
    discovery[id] = low[id] = ++time;

    Aresta* aresta = listaAdj.at(id)->arestas;
    while (aresta != nullptr) {
        int vizinho = aresta->destino;
        if (!visitados[vizinho]) {
            dfs_ponte(vizinho, id, discovery, low, visitados, time, temPonte);

            low[id] = std::min(low[id], low[vizinho]);
            if (low[vizinho] > discovery[id]) {
                temPonte = true; // Aresta (id, vizinho) é uma ponte
            }
        } else if (vizinho != parent) {
            low[id] = std::min(low[id], discovery[vizinho]);
        }
        aresta = aresta->prox;
    }
}