#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <queue>

using namespace std;

class GrafoLista : public Grafo {
public:
    GrafoLista(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada);
    ~GrafoLista();

    bool eh_bipartido() const override;
    int n_conexo() const override;
    int get_grau(int vertice) const override;
    bool possui_articulacao() const override;
    bool possui_ponte() const override;
    bool eh_completo() const override;
    bool eh_arvore() const override;

    void novo_grafo(const string& nomeArquivo);

    void carregar_grafo(const string& nomeArquivo) override;
    void imprimir_grafo(const string& nomeArquivo) const override;

    void adicionar_aresta(int origem, int destino, int peso = 1); // Adiciona aresta com peso
    void adicionar_vertice(int id); // Adiciona um novo vértice ao grafo

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
        Vertice(int id) : id(id), arestas(nullptr) {}

        void adicionar_aresta(int destino, int peso) {
            Aresta* nova = new Aresta(destino, peso);
            nova->prox = arestas;
            arestas = nova;
        }
    };

    unordered_map<int, Vertice*> listaAdj;

    void dfs(int id, unordered_map<int, bool>& visitados) const;
    void dfs_pontes(int id, int parent, unordered_map<int, int>& discovery,
                    unordered_map<int, int>& low, int& time, bool& temPonte);
    Vertice* get_vertice(int id) const;
    void dfs_articulacao(int id, int parent, unordered_map<int, int>& discovery,
                          unordered_map<int, int>& low, unordered_map<int, bool>& visitados,
                          int& time, bool& temArticulacao) const;
    void dfs_ponte(int id, int parent, unordered_map<int, int>& discovery,
                   unordered_map<int, int>& low, unordered_map<int, bool>& visitados,
                   int& time, bool& temPonte) const;
};

#endif // GRAFOLISTA_H