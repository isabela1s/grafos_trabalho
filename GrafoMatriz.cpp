#include "GrafoMatriz.h"
#include <iostream>
#include <fstream>

using namespace std;

GrafoMatriz::GrafoMatriz(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada)
    : Grafo(numVertices, direcionado, verticePonderado, arestaPonderada) {
    matrizAdj = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        matrizAdj[i] = new int[numVertices];
        for (int j = 0; j < numVertices; j++) {
            matrizAdj[i][j] = 0; // Inicializa sem arestas
        }
    }
}

GrafoMatriz::~GrafoMatriz() {
    for (int i = 0; i < get_ordem(); i++) {
        delete[] matrizAdj[i];
    }
    delete[] matrizAdj;
}

void GrafoMatriz::carregar_grafo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    int origem, destino, peso;
    while (arquivo >> origem >> destino >> peso) {
        matrizAdj[origem][destino] = peso;
        if (!eh_direcionado()) {
            matrizAdj[destino][origem] = peso;
        }
    }

    arquivo.close();
}

void GrafoMatriz::imprimir_grafo(const string& nomeArquivo) const {
    ofstream arquivo(nomeArquivo);
    if (!arquivo) {
        cerr << "Erro ao criar arquivo de saída!" << endl;
        return;
    }

    for (int i = 0; i < get_ordem(); i++) {
        for (int j = 0; j < get_ordem(); j++) {
            arquivo << matrizAdj[i][j] << " ";
        }
        arquivo << endl;
    }
}

int* GrafoMatriz::get_vizinhos(int vertice, int& tamanho) const {
    tamanho = 0;
    for (int i = 0; i < get_ordem(); i++) {
        if (matrizAdj[vertice][i] > 0) tamanho++;
    }

    int* vizinhos = new int[tamanho];
    int index = 0;
    for (int i = 0; i < get_ordem(); i++) {
        if (matrizAdj[vertice][i] > 0) {
            vizinhos[index++] = i;
        }
    }
    return vizinhos;
}

bool GrafoMatriz::existe_aresta(int origem, int destino) const {
    return matrizAdj[origem][destino] != 0;
}

void GrafoMatriz::remover_vertice(int vertice) {
    for (int i = 0; i < get_ordem(); i++) {
        matrizAdj[i][vertice] = 0;
        matrizAdj[vertice][i] = 0;
    }
}

void GrafoMatriz::remover_aresta(int origem, int destino) {
    matrizAdj[origem][destino] = 0;
    if (!eh_direcionado()) {
        matrizAdj[destino][origem] = 0;
    }
}

bool GrafoMatriz::eh_vizinho(int u, int vizinho) const {
    return matrizAdj[u][vizinho] > 0;
}

void GrafoMatriz::dfs(int vertice, int* visitados) const {
    visitados[vertice] = 1;

    int tamanho;
    int* vizinhos = get_vizinhos(vertice, tamanho);
    for (int i = 0; i < tamanho; i++) {
        if (visitados[vizinhos[i]] == 0) {
            dfs(vizinhos[i], visitados);
        }
    }
    delete[] vizinhos;
}

Grafo* GrafoMatriz::copia() const {
    GrafoMatriz* novoGrafo = new GrafoMatriz(numVertices, direcionado, verticePonderado, arestaPonderada);

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (matrizAdj[i][j] != 0) {
                novoGrafo->matrizAdj[i][j] = matrizAdj[i][j];
            }
        }
    }

    return novoGrafo;
}
