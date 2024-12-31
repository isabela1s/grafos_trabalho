#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <iostream>

class Grafo {
public:
    //virtual bool eh_bipartido() = 0;
    //virtual int n_conexo() = 0;
    //virtual int get_grau() = 0;
    int get_ordem();
    bool eh_direcionado();
    bool vertice_ponderado();
    bool aresta_ponderada();
    bool eh_completo();
    bool eh_arvore();
    bool possui_articulacao();
    bool possui_ponte();
    void carrega_grafo();
    void novo_grafo();
    virtual void imprimir_grafo(const std::string& nomeArquivo) = 0;  // Método virtual

    virtual ~Grafo();  // Destrutor virtual

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
