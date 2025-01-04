#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "Grafo.h"

class Aresta {
    public:
      int destino;
      Aresta* prox;

      Aresta(int destino);
};

class Vertice {
  public:
    int id;
    Aresta* arestas;
    Vertice* prox;

    Vertice(int id);
    void adicionaAresta(int destino);
};

class GrafoLista {
  private:
    Vertice* vertices;

  public:
    GrafoLista();
    ~GrafoLista();

    void addVertice(int id);
    void addAresta(int origgem, int destino);
    void imprimeGrafo();
};

#endif //GRAFO_LISTA_H
