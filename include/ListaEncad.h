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

        No* novo_no(int val, int peso); 
        void nova_aresta(No* origem, int destino, int peso);
        void deleta_no(int val); 
        void deleta_aresta(int origem, int destino);

        No* primeiro;

    private:
        No* encontrarNo(int val);
};

#endif