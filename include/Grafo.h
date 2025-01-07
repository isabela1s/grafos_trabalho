#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <iostream>

class Grafo {
public:
    virtual bool eh_bipartido() = 0;
    virtual int n_conexo() = 0;
    virtual int get_grau() = 0;
    int get_ordem();
    bool eh_direcionado();
    bool vertice_ponderado();
    bool aresta_ponderada();
    bool eh_completo();
    bool eh_arvore(int numVertices);
    virtual bool possui_articulacao() = 0;
    virtual bool possui_ponte() = 0;
    void carrega_grafo();
    void novo_grafo();
    virtual void imprimir_grafo(const std::string& nomeArquivo) = 0;

    virtual ~Grafo();  // Destrutor virtual
    virtual bool eh_conexo() = 0;

    Grafo(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada);
protected:
    int numVertices;
    int numArestas;
    bool direcionado;
    bool verticePonderado;
    bool arestaPonderada;
    int* pesosVertices;
};

#endif // GRAFO_H
