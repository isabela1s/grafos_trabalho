#include "../include/No.h"
#include <iostream>

No::No(int val, int p) {
    info = val;
    peso = p;
    prox = nullptr;
}

No::~No() {}

int No::getInfo() { return info; }

int No::getPeso() { return peso; }

No* No::getProx() { return prox; }

void No::setInfo(int val) { info = val; }

void No::setPeso(int p) { peso = p; }

void No::setProx(No *p) { prox = p; }

