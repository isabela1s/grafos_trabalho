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

    int numVerticesArquivo;
    arquivo >> numVerticesArquivo;

    // Verifica se precisamos redimensionar a matriz de adjacência
    if (numVerticesArquivo != numVertices) {
        // Liberar matriz antiga
        for (int i = 0; i < numVertices; i++) {
            delete[] matrizAdj[i];
        }
        delete[] matrizAdj;

        // Criar nova matriz com tamanho correto
        numVertices = numVerticesArquivo;
        matrizAdj = new int*[numVertices];
        for (int i = 0; i < numVertices; i++) {
            matrizAdj[i] = new int[numVertices];
            for (int j = 0; j < numVertices; j++) {
                matrizAdj[i][j] = 0; // Inicializa sem arestas
            }
        }
    }

    int origem, destino, peso;
    bool temPeso = arestaPonderada;

    while (arquivo >> origem >> destino) {
        // Se o grafo for ponderado, lê o peso. Caso contrário, assume peso 1.
        if (temPeso) {
            arquivo >> peso;
        } else {
            peso = 1;
        }

        // Verifica se os índices estão dentro dos limites válidos
        if (origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices) {
            cerr << "Erro: Índices de vértices fora do intervalo válido! (" << origem << ", " << destino << ")" << endl;
            continue;
        }

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
