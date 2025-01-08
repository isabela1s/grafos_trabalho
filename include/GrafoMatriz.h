#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"
#include <vector>
#include <string>
#include <iostream>

class GrafoMatriz : public Grafo {
public:
    GrafoMatriz(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada);
    ~GrafoMatriz();

    bool eh_bipartido() const override;
    int n_conexo() const override;
    int get_grau(int vertice) const override;
    bool possui_articulacao() const override;
    bool possui_ponte() const override;
    bool eh_completo() const override;
    bool eh_arvore() const override;

    void carregar_grafo(const std::string& nomeArquivo) override;
    void imprimir_grafo(const std::string& nomeArquivo) const override;

    void adicionar_vertice(); // Adiciona um vértice na matriz (aumenta tamanho)
    void adicionar_aresta(int origem, int destino, int peso = 1); // Adiciona aresta com peso

private:
    std::vector<std::vector<int>> matrizAdj; // Matriz de adjacência
    void dfs(int vertice, std::vector<bool>& visitados) const; // Versão original (para n_conexo)
    void dfs(int vertice, std::vector<bool>& visitados, const std::vector<std::vector<int>>& matriz) const; // Para possui_articulacao

};

#endif // GRAFOMATRIZ_H