#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"
#include <iostream>

class GrafoMatriz : public Grafo {
public:
    GrafoMatriz(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada);
    ~GrafoMatriz();

    void carregar_grafo(const std::string& nomeArquivo);
    void imprimir_grafo(const std::string& nomeArquivo) const;

private:
    int** matrizAdj;
    int* get_vizinhos(int vertice, int& tamanho) const override;
    bool existe_aresta(int origem, int destino) const override;
    Grafo* copia() const override;
    void remover_vertice(int vertice) override;
    void remover_aresta(int origem, int destino) override;
    bool eh_vizinho(int u, int vizinho) const override;
    void dfs(int vertice, int* visitados) const override;
};

#endif // GRAFOMATRIZ_H
