#include "GrafoLista.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>
#include <random>

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
    // Adiciona aresta do vértice origem para o vértice destino
    listaAdj[origem]->adicionar_aresta(destino, peso);

    // Se o grafo for não direcionado, adiciona aresta no sentido inverso
    listaAdj[destino]->adicionar_aresta(origem, peso);
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

void GrafoLista::imprimir_grafo(const string& nomeArquivo) const {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
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
            if (!primeiraAresta) {
                arquivo << " "; // Adiciona espaço entre os destinos
            }

            // Se houver peso, imprime o peso da aresta
            arquivo << aresta->destino;
            if (aresta->peso != -1) {
                arquivo << " (peso " << aresta->peso << ")";
            }

            aresta = aresta->prox;
            primeiraAresta = false;
        }
        arquivo << endl;
    }

    arquivo.close();
    cout << "Grafo salvo em " << nomeArquivo << endl;
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
void GrafoLista::carregar_grafo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
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
    unordered_map<int, int> cores;
    for (const auto& pair : listaAdj) {
        cores[pair.first] = -1; // Não colorido
    }

    for (const auto& pair : listaAdj) {
        int id = pair.first;
        if (cores[id] == -1) {
            // BFS para verificar bipartição
            queue<int> fila;
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

void GrafoLista::dfs(int id, unordered_map<int, bool>& visitados) const {
    visitados[id] = true; // Marca o vértice como visitado
    Aresta* aresta = listaAdj.at(id)->arestas;
    while (aresta != nullptr) {
        if (!visitados[aresta->destino]) {
            dfs(aresta->destino, visitados); // Chama recursivamente para o próximo vértice
        }
        aresta = aresta->prox;
    }
}

void GrafoLista::dfs_articulacao(int id, int parent, unordered_map<int, int>& discovery,
                                  unordered_map<int, int>& low, unordered_map<int, bool>& visitados,
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
            low[id] = min(low[id], low[vizinho]);
            if (parent == -1 && filhos > 1) {
                temArticulacao = true;
            }
            if (parent != -1 && low[vizinho] >= discovery[id]) {
                temArticulacao = true;
            }
        } else if (vizinho != parent) {
            low[id] = min(low[id], discovery[vizinho]);
        }
        aresta = aresta->prox;
    }
}

void GrafoLista::dfs_ponte(int id, int parent, unordered_map<int, int>& discovery,
                           unordered_map<int, int>& low, unordered_map<int, bool>& visitados,
                           int& time, bool& temPonte) const {
    visitados[id] = true;
    discovery[id] = low[id] = ++time;

    Aresta* aresta = listaAdj.at(id)->arestas;
    while (aresta != nullptr) {
        int vizinho = aresta->destino;
        if (!visitados[vizinho]) {
            dfs_ponte(vizinho, id, discovery, low, visitados, time, temPonte);

            low[id] = min(low[id], low[vizinho]);
            if (low[vizinho] > discovery[id]) {
                temPonte = true; // Aresta (id, vizinho) é uma ponte
            }
        } else if (vizinho != parent) {
            low[id] = min(low[id], discovery[vizinho]);
        }
        aresta = aresta->prox;
    }
}

void GrafoLista::novo_grafo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de configuração." << endl;
        return;
    }

    // Lê as informações do arquivo de configuração
    int numVertices, numArestas;
    arquivo >> numVertices >> numArestas;

    // Cria o grafo com o número de vértices
    listaAdj.clear(); // Limpa a lista de adjacência antes de criar o novo grafo
    for (int i = 0; i < numVertices; ++i) {
        listaAdj[i] = new Vertice(i);
    }

    // Gerador de números aleatórios
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, numVertices - 1); // Para os vértices
    uniform_int_distribution<int> weightDistribution(1, 10);  // Para os pesos (caso o grafo seja ponderado)

    // Gera as arestas aleatórias
    for (int i = 0; i < numArestas; ++i) {
        int origem = distribution(generator);
        int destino = distribution(generator);

        // Garante que não haverá laços (vértice se conectando consigo mesmo)
        while (origem == destino) {
            destino = distribution(generator);
        }

        // Gera um peso aleatório
        int peso = weightDistribution(generator);

        // Adiciona a aresta no grafo (não direcionado)
        listaAdj[origem]->adicionar_aresta(destino, peso);
        listaAdj[destino]->adicionar_aresta(origem, peso);  // Como o grafo é não direcionado

    }

    cout << "Grafo aleatório gerado com " << numVertices << " vértices e " << numArestas << " arestas." << endl;
}