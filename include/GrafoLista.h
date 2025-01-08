#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <stack>
#include <iostream>

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

    void carregar_grafo(const std::string& nomeArquivo) override;
    void imprimir_grafo(const std::string& nomeArquivo) const override;

    void adicionar_vertice(int id);
    void adicionar_aresta(int origem, int destino);

private:
    struct Aresta {
        int destino;
        Aresta* prox;
        Aresta(int d) : destino(d), prox(nullptr) {}
    };

    struct Vertice {
        int id;
        Aresta* arestas;
        Vertice(int id) : id(id), arestas(nullptr) {}

        void adicionar_aresta(int destino) {
            Aresta* nova = new Aresta(destino);
            nova->prox = arestas;
            arestas = nova;
        }
    };

    std::unordered_map<int, Vertice*> listaAdj;
    void dfs(int id, std::unordered_map<int, bool>& visitados) const;
    void dfs_pontes(int id, int parent, std::unordered_map<int, int>& discovery,
                    std::unordered_map<int, int>& low, int& time, bool& temPonte);
    Vertice* get_vertice(int id) const;

};

#endif // GRAFOLISTA_H