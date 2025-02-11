#ifndef LISTAENCAD_H
#define LISTAENCAD_H

#include "No.h"

class ListaEncad {
    public:
        ListaEncad();
        ~ListaEncad();

        void insere(int val, int peso);
        void removeNo(int val);
        bool busca(int val);
        void imprimeLista();
        void get_adj(int adjacentes[], int &size) const;

    private:
        No* primeiro;
};

#endif