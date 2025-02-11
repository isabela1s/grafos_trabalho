#include "GrafoLista.h"
#include <fstream>
#include <iostream>

using namespace std;

GrafoLista::GrafoLista(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada)
    : Grafo(numVertices, direcionado, verticePonderado, arestaPonderada), listaAdj(nullptr) {
}

GrafoLista::~GrafoLista() {
    delete[] listaAdj;
    delete[] pesosVertices;
}

void GrafoLista::adicionar_vertice(int id) {
    if (id >= numVertices) {
        cerr << "Erro: ID do vértice fora do limite." << endl;
        return;
    }
}

void GrafoLista::imprimir_grafo(const string& nomeArquivo) const {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
        return;
    }

    for (int i = 0; i < numVertices; i++) {
        arquivo << "Vértice " << i + 1 << ": ";
        cout << "Processando vértice " << i + 1 << endl;

        listaAdj[i].imprimeLista();

        arquivo << endl;
    }

    arquivo.close();
    cout << "Grafo salvo em " << nomeArquivo << endl;


}

int* GrafoLista::get_vizinhos(int vertice, int& tamanho) const {
    if (vertice >= numVertices) {
        tamanho = 0;
        return nullptr;
    }

    ListaEncad* lista = &listaAdj[vertice];
    int count = 0;

    // Contar quantos vizinhos existem
    No* atual = lista->primeiro;
    while (atual) {
        count++;
        atual = atual->getProx();
    }

    tamanho = count;
    if (count == 0) {
        return nullptr;
    }

    // Criar array e armazenar vizinhos
    int* vizinhos = new int[count];
    atual = lista->primeiro;
    int i = 0;
    while (atual) {
        vizinhos[i++] = atual->getInfo();
        atual = atual->getProx();
    }

    return vizinhos;
}

bool GrafoLista::existe_aresta(int origem, int destino) const {
    if (origem >= numVertices || destino >= numVertices) {
        return false;
    }

    return listaAdj[origem].busca(destino + 1);
}

void GrafoLista::remover_vertice(int vertice) {
    if (vertice >= numVertices) {
        cerr << "Erro: Vértice fora do limite." << endl;
        return;
    }

    listaAdj[vertice].~ListaEncad(); // Liberar a lista encadeada do vértice

    for (int i = 0; i < numVertices; i++) {
        listaAdj[i].removeNo(vertice + 1);
    }
}

void GrafoLista::remover_aresta(int origem, int destino) {
    if (origem >= numVertices || destino >= numVertices) {
        cerr << "Erro: Vértice fora do limite." << endl;
        return;
    }

    listaAdj[origem].removeNo(destino + 1);
    numArestas--;
}

bool GrafoLista::eh_vizinho(int u, int vizinho) const {
    return existe_aresta(u, vizinho);
}

Grafo* GrafoLista::copia() const {
    GrafoLista* novoGrafo = new GrafoLista(numVertices, direcionado, verticePonderado, arestaPonderada);

    for (int i = 0; i < numVertices; i++) {
        ListaEncad* lista = &listaAdj[i];
        No* atual = lista->primeiro;

        while (atual) {
            int destino = atual->getInfo();
            int peso = atual->getPeso();
            novoGrafo->adicionar_aresta(i, destino - 1, peso);
            atual = atual->getProx();
        }
    }

    return novoGrafo;
}

void GrafoLista::adicionar_aresta(int origem, int destino, int peso) {
    if (origem >= numVertices || destino >= numVertices) {
        cerr << "Erro: Vértice fora do limite." << endl;
        return;
    }

    listaAdj[origem].insere(destino + 1, peso);
    numArestas++;
}

void GrafoLista::dfs(int vertice, int visitados[]) const {
    visitados[vertice] = 1;

    int tamanho = 0;
    int* vizinhos = get_vizinhos(vertice, tamanho);

    for (int i = 0; i < tamanho; i++) {
        if (!visitados[vizinhos[i]]) {
            dfs(vizinhos[i], visitados);
        }
    }

    delete[] vizinhos;
}
