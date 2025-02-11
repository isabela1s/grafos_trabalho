#include "Grafo.h"
#include <iostream>

using namespace std;

bool Grafo::eh_bipartido() const {
    int cor[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        cor[i] = -1; // -1 significa que o vértice não foi colorido ainda
    }

    for (int i = 0; i < numVertices; ++i) {
        if (cor[i] == -1) {
            cor[i] = 0;
            if (!eh_bipartido_util(i, cor)) {
                return false;
            }
        }
    }
    return true;
}

bool Grafo::eh_bipartido_util(int v, int cor[]) const {
    int adjacentes[100];
    int size;
    get_adjacentes(v, adjacentes, size);

    for (int i = 0; i < size; ++i) {
        int adj = adjacentes[i];
        if (cor[adj] == -1) {
            cor[adj] = 1 - cor[v];
            if (!eh_bipartido_util(adj, cor)) {
                return false;
            }
        } else if (cor[adj] == cor[v]) {
            return false; 
        }
    }
    return true;


int Grafo::n_conexo() const {
    bool visitado[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        visitado[i] = false;
    }
    
    int componentes = 0;
    for(int i = 0; i < numVertices; ++i) {
        if (!visitado[i]) {
            DFS(i, visitado);
            componentes++;
        }
    }
    return componentes;
}

void Grafo::DFS(int v, bool visitado[]) const {
    visitado[v] = true;
    int adjacentes[100];
    int size;
    get_adjacentes(v, adjacentes, size);

    for (int i = 0; i < size; ++i) {
        int adj = adjacentes[i];
        if (!visitado[adj]) {
            DFS(adj, visitado);
        }
    }
}

int Grafo::get_grau(int vertice) const {
    int adjacentes[100]; // Supondo que no máximo 100 adjacentes
    int size;
    get_adjacentes(vertice, adjacentes, size);
    return size;


bool Grafo::possui_ponte() const {
    int disc[numVertices], low[numVertices];
    bool visitado[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        visitado[i] = false;
        disc[i] = low[i] = -1;
    }

    int tempo = 0;
    for (int i = 0; i < numVertices; ++i) {
        if (!visitado[i]) {
            if (DFS_ponte(i, -1, visitado, disc, low, tempo)) {
                return true;
            }
        }
    }
    return false;
}

bool Grafo::DFS_ponte(int u, int pai, bool visitado[], int disc[], int low[], int& tempo) const {
    visitado[u] = true;
    disc[u] = low[u] = ++tempo;

    int adjacentes[100];
    int size;
    get_adjacentes(u, adjacentes, size);

    for (int i = 0; i < size; ++i) {
        int adj = adjacentes[i];
        if (!visitado[adj]) {
            if (DFS_ponte(adj, u, visitado, disc, low, tempo)) {
                return true;
            }
            low[u] = min(low[u], low[adj]);

            if (low[adj] > disc[u]) {
                return true;  // Encontrou uma ponte
            }
        } else if (adj != pai) {
            low[u] = min(low[u], disc[adj]);
        }
    }
    return false;


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
