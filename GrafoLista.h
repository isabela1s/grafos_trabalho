#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"
#include <iostream>

class GrafoLista : public Grafo {
public:
    GrafoLista(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada);
    ~GrafoLista();

    void imprimir_grafo(const std::string& nomeArquivo) const;

    void adicionar_vertice(int id);
    void adicionar_aresta(int origem, int destino, int peso = 1);

private:
    struct Aresta {
        int destino;
        int peso;
        Aresta* prox;
        Aresta(int d, int p) : destino(d), peso(p), prox(nullptr) {}
    };

    struct Vertice {
        int id;
        Aresta* arestas;
        Vertice(int i) : id(i), arestas(nullptr) {}
        void adicionar_aresta(int dest, int pes) {
            Aresta* nova_aresta = new Aresta(dest, pes);
            nova_aresta->prox = arestas;
            arestas = nova_aresta;
        }
    };

    struct NoVertice {
        Vertice* vertice;
        NoVertice* prox;
        NoVertice(Vertice* v) : vertice(v), prox(nullptr) {}
    };

    NoVertice* listaAdj;

    int* get_vizinhos(int vertice, int& tamanho) const override;
    bool existe_aresta(int origem, int destino) const override;
    Grafo* copia() const override;
    void remover_vertice(int vertice) override;
    void remover_aresta(int origem, int destino) override;
    bool eh_vizinho(int u, int vizinho) const override;
    void dfs(int vertice, int* visitados) const override;
};



#endif // GRAFOLISTA_H
