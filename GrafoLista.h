#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"
#include "include/ListaEncad.h"
#include <string>
#include <iostream>

class GrafoLista : public Grafo {
    private:
        ListaEncad* listaAdj;

    public:
        GrafoLista(const char* nomeArquivo);
        ~GrafoLista();

        void insereAresta(int origem, int destino, int peso = 0);
        void get_adjacentes(int v, int adjacentes[], int &size) const;

        void imprimeGrafo();
};

#endif // GRAFOLISTA_H