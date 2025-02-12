#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"
#include <iostream>
#include <vector>

class GrafoMatriz : public Grafo {
public:
    GrafoMatriz(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada);
    ~GrafoMatriz();

    void carregar_grafo(const std::string& nomeArquivo);
    void imprimir_grafo(const std::string& nomeArquivo) const;

    void novo_no();
    void nova_aresta(int origem, int destino, int peso);
    void deleta_no(int no);
    void deleta_aresta(int origem, int destino);

private:
    //int** matrizAdj;

    int capacidade; 
    void redimensionar_matriz(); // Redimensiona a matriz quando necessário
    vector<vector<int>> matrizAdj; // Matriz de adjacência
    //void dfs(int vertice, vector<bool>& visitados) const; // Versão original (para n_conexo)
    //void dfs(int vertice, vector<bool>& visitados, const vector<vector<int>>& matriz) const;

    int* get_vizinhos(int vertice, int& tamanho) const override;
    bool existe_aresta(int origem, int destino) const override;
    Grafo* copia() const override;
    void remover_vertice(int vertice) override;
    void remover_aresta(int origem, int destino) override;
    bool eh_vizinho(int u, int vizinho) const override;
    void dfs(int vertice, int* visitados) const override;
};

#endif // GRAFOMATRIZ_H
