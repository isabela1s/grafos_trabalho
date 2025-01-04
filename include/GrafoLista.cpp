#include "GrafoLista.h"

using namespace std;

Aresta::Aresta(int destino) {
  this->destino = destino;
  this->prox = nullptr;
}

Vertice::Vertice(int id) {
  this->id = id;
  this->arestas = nullptr;
  this->prox = nullptr;
}

void Vertice::adicionaAresta(int destino) {
  Aresta* newAresta = new Aresta(destino);
  newAresta->prox = this->arestas;
  this->arestas = newAresta;
}

GrafoLista::GrafoLista() {
  this->vertices = nullptr;
}

GrafoLista::~GrafoLista() {
  Vertice* vTemp = this->vertices;
  while (vTemp != nullptr) {
    Aresta* aTemp = vTemp->arestas;
    while (aTemp != nullptr) {
      Aresta* newAresta = aTemp;
      aTemp = aTemp->prox;
      delete newAresta;
    }
    Vertice* newVertice = vTemp;
    vTemp = vTemp->prox;
    delete newVertice;
  }
}
void GrafoLista::addVertice(int id) {
  Vertice* newVertice = new Vertice(id);
  newVertice->prox = this->vertices;
  this->vertices = newVertice;
}

void GrafoLista::addAresta(int origem, int destino) {
  Vertice* vAtual = this->vertices;
  while (vAtual != nullptr) {
    if (vAtual->id == origem) {
      vAtual->adicionaAresta(destino);
      return;
    }
    vAtual = vAtual->prox;
  }

  addVertice(origem);
  vertices->adicionaAresta(destino);
}

void GrafoLista::imprimeGrafo() {
  Vertice* vAtual = this->vertices;
  while (vAtual != nullptr) {
    cout << "Vértice " << vAtual->id << " : ";
    Aresta* aAtual = vAtual->arestas;
    while (aAtual != nullptr) {
      cout << " -> " << aAtual->destino;
      aAtual = aAtual->prox;
    }
    cout << endl;
    vAtual = vAtual->prox;
  }
}