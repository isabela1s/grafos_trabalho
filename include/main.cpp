#include <iostream>
#include "Grafo.h"
#include "GrafoLista.h"
#include "GrafoMatriz.h"

using namespace std;

int main() {
    // Criar um grafo usando matriz de adjacência
    Grafo* grafo1 = new GrafoMatriz(5, true, true, true); // 5 vértices, não direcionado, sem pesos nos vértices, arestas ponderadas
    grafo1->imprimir_grafo("grafo.txt");
    delete grafo1;

    // Criar um grafo usando lista de adjacência
    //Grafo* grafo2 = new GrafoLista(4, true, true, false); // 4 vértices, direcionado, pesos nos vértices, arestas não ponderadas
    //grafo2->imprimir_grafo();
    //delete grafo2;

    return 0;
}
