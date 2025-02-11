#include "../include/ListaEncad.h"
#include <iostream>

using namespace std;

ListaEncad::ListaEncad() { primeiro = nullptr; }

ListaEncad::~ListaEncad() {
    No *p = primeiro;
    while (p != nullptr) {
        No *t = p->getProx();
        delete p;

        p = t;
    }
    
}

void ListaEncad::insere(int val, int peso) {
    No* novo = new No(val, peso);
    novo->setProx(primeiro);
    primeiro = novo;
}

void ListaEncad::removeNo(int val) {
    if (primeiro == nullptr) {
        cout << "Lista vazia! Nada a remover." << endl;
        return;
    }

    No *p = primeiro;
    No *anterior = nullptr;

    while (p != nullptr && p->getInfo() != val) {
        anterior = p;
        p = p->getProx();
    }

    if (p == nullptr) {
        cout << "Valor " << val << " não encontrado na lista." << endl;
        return;
    }

    if (anterior == nullptr) {
        primeiro = p->getProx();
    } else {
        anterior->setProx(p->getProx());
    }

    delete p;

}


bool ListaEncad::busca(int val) {
    No* p = primeiro;

    while (p != nullptr) {
        if(p->getInfo() == val)
            return true;

        p = p->getProx();
    }

    return false;
    
}

void ListaEncad::imprimeLista() {
    No* p = primeiro;
    while (p != nullptr) {
        cout << p->getInfo() << " (" << p->getPeso() << ") -> ";
        p = p->getProx();
    }
    cout << "NULL" << endl;
}