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

class GrafoLista : public Grafo {
  private:
    Vertice* vertices;

    int getNumVertices();
    Vertice* getVertice(int id);
    void dfs(Vertice* vertice, bool visitado[]);
  public:
    GrafoLista();
    ~GrafoLista();

    void addVertice(int id);
    void addAresta(int origgem, int destino);
    void imprimir_grafo(const std::string& nomeArquivo) override;
    int n_conexo() override;
    bool eh_bipartido() override;
    int get_grau() override;
    bool possui_ponte() override;
    bool possui_articulacao() override;
    void carregar_grafo(const std::string& nomeArquivo);

    bool eh_conexo() override;
};

#endif //GRAFO_LISTA_H
