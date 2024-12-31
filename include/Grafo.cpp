#include "grafo.h"
#include <iostream>
#include <fstream>

using namespace std;

// Construtor da classe Grafo
Grafo::Grafo(int numVerticesParam, bool direcionadoParam, bool verticePonderadoParam, bool arestaPonderadaParam) {
    numVertices = numVerticesParam;
    direcionado = direcionadoParam;
    verticePonderado = verticePonderadoParam;
    arestaPonderada = arestaPonderadaParam;
    numArestas = 0; // Inicialmente sem arestas
}

// Destrutor da classe Grafo
Grafo::~Grafo() {
    // As classes derivadas vão lidar com a memória específica delas
}

// Retorna a ordem do grafo (número de vértices)
int Grafo::get_ordem() {
    return numVertices;
}

// Retorna se o grafo é direcionado
bool Grafo::eh_direcionado() {
    return direcionado;
}

// Retorna se os vértices possuem peso
bool Grafo::vertice_ponderado() {
    return verticePonderado;
}

// Retorna se as arestas possuem peso
bool Grafo::aresta_ponderada() {
    return arestaPonderada;
}

// Método básico para exibir informações do grafo
void Grafo::imprimir_grafo() {
    cout << "Grafo: " << endl;
    cout << " - Ordem (número de vértices): " << numVertices << endl;
    cout << " - Direcionado: " << (direcionado ? "Sim" : "Não") << endl;
    cout << " - Vértices ponderados: " << (verticePonderado ? "Sim" : "Não") << endl;
    cout << " - Arestas ponderadas: " << (arestaPonderada ? "Sim" : "Não") << endl;
}
