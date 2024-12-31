// GrafoMatriz.h

#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"
#include <vector>

class GrafoMatriz : public Grafo {
public:
    GrafoMatriz(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada);
    ~GrafoMatriz();

    bool eh_bipartido();
    //int n_conexo() override;
    //int get_grau() override;
    void imprimir_grafo(const std::string& nomeArquivo) override;
    void carregar_grafo(const std::string& nomeArquivo);
    void adicionar_aresta(int origem, int destino, int peso = 1);
    void remover_aresta(int origem, int destino);
    int** get_matriz();

private:
    int** matrizAdjacencia;
    void inicializar_matriz();
    void liberar_matriz();
};

#endif // GRAFOMATRIZ_H
