#include "../include/No.h"
#include <iostream>

using namespace std;

No::No(int val, int p) {
    info = val;
    peso = p;
    prox = nullptr;
}

No::~No() {}

int No::getInfo() { 
    if(!this) {
        cerr << "Erro: Tentativa de acessar um nó inválido em getInfo()" << endl;
        return -1;
    }

    return info; 
    
}

int No::getPeso() { return peso; }

No* No::getProx() { return prox; }

void No::setInfo(int val) { info = val; }

void No::setPeso(int p) { peso = p; }

void No::setProx(No *p) { prox = p; }
