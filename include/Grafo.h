#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <iostream>

class Grafo {
  public:
    bool eh_bipartido(); // Verifica se o grafo é bipartido
    int n_conexo(); // Indica a quantidade de componentes conexas do grafo
    int get_grau(); // Indica o grau do grafo
    int get_ordem(); // Indica a ordem do grafo
    bool eh_direcionando(); // Verifica se o grafo é eh_direcionado
    bool vertice_ponderado(); // Verifica se os vertices do grafo possuem peso
    bool aresta_ponderada(); // Verifica se as arestas possuem peso
    bool eh_completo(); // Verifica se o grafo é completo
    bool eh_arvore(); // Verifica se o grafo é uma arvore
    bool possui_articulacao(); // Verifica se existe pelo menos 1 vertice de articulação
    bool possui_ponte(); // Verifica a existência de uma aresta ponte
    void carrega_grafo(); // Lê um txt com um grafo e carrega o mesmo
    void novo_grafo(); // Lê um txt de config. e gera um grafo

  protected:
    int numVertices;
};

#endif //GRAFO_H
