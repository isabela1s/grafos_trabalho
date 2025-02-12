#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <string>

class Grafo {
public:
    Grafo(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada);
    virtual ~Grafo();

    void carregar_grafo(const std::string& nomeArquivo);
    virtual void imprimir_grafo(const std::string& nomeArquivo) const = 0;

    // Funções agora na classe base
    int get_grau(int vertice) const;
    int n_conexo() const;
    int get_ordem() const;
    bool eh_direcionado() const;
    bool vertice_ponderado() const;
    bool aresta_ponderada() const;
    bool eh_completo() const;
    bool eh_arvore() const;
    bool eh_bipartido() const;
    bool possui_articulacao() const;
    bool possui_ponte() const;


protected:
    int numVertices;
    int numArestas;
    bool direcionado;
    bool verticePonderado;
    bool arestaPonderada;
    int* pesosVertices;

    virtual int* get_vizinhos(int vertice, int& tamanho) const = 0;
    virtual bool existe_aresta(int origem, int destino) const = 0;
    virtual Grafo* copia() const = 0; // Função para copiar o grafo
    virtual void remover_vertice(int vertice) = 0;
    virtual void remover_aresta(int origem, int destino) = 0;
    virtual bool eh_vizinho(int u, int vizinho) const = 0;
    virtual void dfs(int vertice, int visitados[]) const = 0;
};

#endif // GRAFO_H
