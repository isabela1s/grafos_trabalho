#ifndef GRAFO_H
#define GRAFO_H

#include <string>

class Grafo {
public:
    Grafo(): numVertices(0), direcionado(false), verticePonderado(false), arestaPonderada(false), pesosVertices(nullptr) {}
    ~Grafo();

    virtual void get_adjacentes(int v, int adjacentes[], int &size) const = 0;

    virtual bool eh_bipartido() const;
    virtual int n_conexo() const;
    virtual int get_grau(int vertice) const;
    virtual bool possui_ponte() const;

    int get_ordem() const;
    bool eh_direcionado() const;
    bool vertice_ponderado() const;
    bool aresta_ponderada() const;
    
    virtual bool eh_completo() const = 0;
    virtual bool eh_arvore() const = 0;
    virtual bool possui_articulacao() const = 0;

protected:
    int numVertices;
    int numArestas;
    bool direcionado;
    bool verticePonderado;
    bool arestaPonderada;
    int* pesosVertices;

    void DFS(int v, bool visitado[]) const;
    bool DFS_ponte(int u, int pai, bool visitado[], int disc[], int low[], int& tempo) const;
    bool DFS_articulacao(int u, int pai, bool visitado[], int disc[], int low[], int& tempo) const;
    bool eh_bipartido_util(int v, int cor[]) const;

};

#endif // GRAFO_H