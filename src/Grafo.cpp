#include "Grafo.h"
#include <iostream>
#include <queue>

using namespace std;

Grafo::Grafo(int numVerticesParam, bool direcionadoParam, bool verticePonderadoParam, bool arestaPonderadaParam)
    : numVertices(numVerticesParam), numArestas(0), direcionado(direcionadoParam),
      verticePonderado(verticePonderadoParam), arestaPonderada(arestaPonderadaParam) {}

Grafo::~Grafo() {}

int Grafo::get_ordem() const {
    return numVertices;
}

bool Grafo::eh_direcionado() const {
    return direcionado;
}

bool Grafo::vertice_ponderado() const {
    return verticePonderado;
}

bool Grafo::aresta_ponderada() const {
    return arestaPonderada;
}

bool Grafo::eh_completo() const {
    int totalArestas = direcionado ? numVertices * (numVertices - 1) : numVertices * (numVertices - 1) / 2;
    return numArestas == totalArestas;
}

bool Grafo::eh_arvore() const {
    return n_conexo() == 1 && numArestas == numVertices - 1;
}

int Grafo::n_conexo() const {
    int* visitados = new int[numVertices];
    for (int i = 0; i < numVertices; i++) visitados[i] = 0;

    int componentes = 0;
    for (int v = 0; v < numVertices; v++) {
        if (visitados[v] == 0) {
            dfs(v, visitados);
            componentes++;
        }
    }
    delete[] visitados;
    return componentes;
}

bool Grafo::eh_bipartido() const {
    int* cor = new int[numVertices];
    for (int i = 0; i < numVertices; i++) cor[i] = -1;

    for (int v = 0; v < numVertices; v++) {
        if (cor[v] == -1) {
            cor[v] = 0;
            queue<int> fila;
            fila.push(v);

            while (!fila.empty()) {
                int u = fila.front();
                fila.pop();
                int tamanho;
                int* vizinhos = get_vizinhos(u, tamanho);
                for (int i = 0; i < tamanho; i++) {
                    int vizinho = vizinhos[i];
                    if (cor[vizinho] == -1) {
                        cor[vizinho] = 1 - cor[u];
                        fila.push(vizinho);
                    } else if (cor[vizinho] == cor[u]) {
                        delete[] cor;
                        delete[] vizinhos;
                        return false;
                    }
                }
                delete[] vizinhos;
            }
        }
    }
    delete[] cor;
    return true;
}

bool Grafo::possui_articulacao() const {
    int originalConexos = n_conexo();

    for (int v = 0; v < numVertices; v++) {
        int grau = get_grau(v);
        if (grau > 0) {
            Grafo* copia = this->copia();
            copia->remover_vertice(v);
            if (copia->n_conexo() > originalConexos) {
                delete copia;
                return true;
            }
            delete copia;
        }
    }
    return false;
}

bool Grafo::possui_ponte() const {
    int originalConexos = n_conexo();

    for (int u = 0; u < numVertices; u++) {
        int tamanho;
        int* vizinhos_u = get_vizinhos(u, tamanho);
        for (int i = 0; i < tamanho; i++) {
            int v = vizinhos_u[i];
            if (v > u) { // Para evitar verificar a mesma aresta duas vezes
                Grafo* copia = this->copia();
                copia->remover_aresta(u, v);
                if (copia->n_conexo() > originalConexos) {
                    delete copia;
                    delete[] vizinhos_u;
                    return true;
                }
                delete copia;
            }
        }
        delete[] vizinhos_u;
    }
    return false;
}

int Grafo::get_grau(int vertice) const {
    int grau = 0;
    int tamanho;
    int* vizinhos = get_vizinhos(vertice, tamanho);
    grau = tamanho;
    delete[] vizinhos;
    return grau;
}

