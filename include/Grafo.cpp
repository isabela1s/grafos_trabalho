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
void Grafo::imprimir_grafo(const std::string& nomeArquivo) {
    cout << "Grafo: " << endl;
    cout << " - Ordem (número de vértices): " << numVertices << endl;
    cout << " - Direcionado: " << (direcionado ? "Sim" : "Não") << endl;
    cout << " - Vértices ponderados: " << (verticePonderado ? "Sim" : "Não") << endl;
    cout << " - Arestas ponderadas: " << (arestaPonderada ? "Sim" : "Não") << endl;
}

bool Grafo::eh_completo()
{
    int verticesTotais = get_ordem();

    // Grafos com menos de 2 vértices não são completos
    if (verticesTotais < 2)
        return false;

    int arestasEsperadas;

    if (direcionado)
        arestasEsperadas = verticesTotais * (verticesTotais - 1);
    else
        arestasEsperadas = (verticesTotais * (verticesTotais - 1)) / 2;

    return numArestas == arestasEsperadas;
}

bool Grafo::eh_arvore(int numVertices)
{
    // Um grafo é árvore se for conexo, ter ao menos 1 vértice e n-1 arestas
    int verticesTotais = get_ordem();

    if (verticesTotais < 1)
        return false;

    if ((numArestas == verticesTotais - 1) && eh_conexo())
        return true;
    else
        return false;
}

