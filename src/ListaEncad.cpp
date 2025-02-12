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

No* ListaEncad::novo_no(int val, int peso) {
    No* novo = new No(val, peso);
    insere(val, peso); // Adiciona o novo nó à lista
    return novo;
}

void ListaEncad::nova_aresta(No* origem, int destino, int peso) {
    if (origem) {
        No* novo = new No(destino, peso);
        novo->setProx(origem->getProx());
        origem->setProx(novo);
    }
}

void ListaEncad::deleta_no(int val) {
    removeNo(val);
}

void ListaEncad::deleta_aresta(int origem, int destino) {
    No* noOrigem = encontrarNo(origem);
    if (!noOrigem) return;

    No* atual = noOrigem->getProx();
    No* anterior = noOrigem;

    while (atual && atual->getInfo() != destino) {
        anterior = atual;
        atual = atual->getProx();
    }

    if (!atual) return;

    anterior->setProx(atual->getProx());
    delete atual;
}

No* ListaEncad::encontrarNo(int val) {
    No* atual = primeiro;
    while (atual) {
        if (atual->getInfo() == val) {
            return atual;
        }
        atual = atual->getProx();
    }
    return nullptr;
}