#include "Grafo.h"
#include <iostream>

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
    // Um grafo completo deve ter todas as arestas possíveis
    int totalArestas = direcionado
                           ? numVertices * (numVertices - 1) // Grafo direcionado
                           : numVertices * (numVertices - 1) / 2; // Grafo não direcionado
    return numArestas == totalArestas;
}

bool Grafo::eh_arvore() const {
    // Um grafo é uma árvore se é conexo e possui exatamente numVertices - 1 arestas
    return n_conexo() == 1 && numArestas == numVertices - 1;
}