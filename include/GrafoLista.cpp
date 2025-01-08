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

void GrafoLista::adicionar_aresta(int origem, int destino) {
    if (listaAdj.find(origem) == listaAdj.end()) {
        adicionar_vertice(origem);
    }
    if (listaAdj.find(destino) == listaAdj.end()) {
        adicionar_vertice(destino);
    }
    listaAdj[origem]->adicionar_aresta(destino);
    if (!direcionado) {
        listaAdj[destino]->adicionar_aresta(origem);
    }
    numArestas++;
}

void GrafoLista::dfs(int id, unordered_map<int, bool>& visitados) const {
    visitados[id] = true;
    for (Aresta* aresta = listaAdj.at(id)->arestas; aresta; aresta = aresta->prox) {
        if (!visitados[aresta->destino]) {
            dfs(aresta->destino, visitados);
        }
    }
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
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return;
    }

    for (const auto& [id, vertice] : listaAdj) {
        arquivo << "Vértice " << id << ":";
        for (Aresta* aresta = vertice->arestas; aresta; aresta = aresta->prox) {
            arquivo << " " << aresta->destino;
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