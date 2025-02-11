#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include <iostream>

#include "Grafo.h"
#include "include/ListaEncad.h"

class GrafoLista : public Grafo {
public:
    GrafoLista(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada);
    ~GrafoLista();
    
    void carregar_grafo(const std::string& nomeArquivo);
    void imprimir_grafo(const std::string& nomeArquivo) const;

    void adicionar_vertice(int id);
    void adicionar_aresta(int origem, int destino, int peso = 1);

private:
    ListaEncad* listaAdj;

    int* get_vizinhos(int vertice, int& tamanho) const;
    bool existe_aresta(int origem, int destino) const override;
    Grafo* copia() const override;
    void remover_vertice(int vertice) override;
    void remover_aresta(int origem, int destino) override;
    bool eh_vizinho(int u, int vizinho) const override;
    void dfs(int vertice, int* visitados) const override;
};



#endif // GRAFOLISTA_H
