#include "GrafoMatriz.h"
#include <iostream>
#include <fstream>
using namespace std;

GrafoMatriz::GrafoMatriz(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada)
    : Grafo(numVertices, direcionado, verticePonderado, arestaPonderada) {
    matrizAdjacencia = new int*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        matrizAdjacencia[i] = new int[numVertices]();
    }
    if (verticePonderado) {
        pesosVertices = new int[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            pesosVertices[i] = 0;  // Defina um valor padrão para os pesos
        }
    }
}

GrafoMatriz::~GrafoMatriz() {
    for (int i = 0; i < numVertices; ++i) {
        delete[] matrizAdjacencia[i];
    }
    delete[] matrizAdjacencia;

    if (pesosVertices) {
        delete[] pesosVertices;
    }
}

void GrafoMatriz::adicionar_aresta(int origem, int destino, int peso) {
    if (origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices) {
        cerr << "Erro: Índice de vértice inválido!" << endl;
        return;
    }

    matrizAdjacencia[origem][destino] = peso;
    if (!direcionado) {
        matrizAdjacencia[destino][origem] = peso;
    }

    numArestas++;
}

void GrafoMatriz::inicializar_matriz() {
    matrizAdjacencia = new int*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        matrizAdjacencia[i] = new int[numVertices]();
    }
}

void GrafoMatriz::liberar_matriz() {
    if (matrizAdjacencia) {
        for (int i = 0; i < numVertices; ++i) {
            delete[] matrizAdjacencia[i];
        }
        delete[] matrizAdjacencia;
        matrizAdjacencia = nullptr;  // Garante que o ponteiro seja nulo após a liberação
    }
}

void GrafoMatriz::imprimir_grafo(const string& nomeArquivo) {
    ofstream arquivo(nomeArquivo);

    if (!arquivo) {
        cout << "Erro ao abrir o arquivo para escrita!" << endl;
        return;
    }

    // Escreve as informações principais do grafo (como grau, ordem, se é direcionado, etc.)
    arquivo << numVertices << " " << (direcionado ? 1 : 0) << " " << (verticePonderado ? 1 : 0)
            << " " << (arestaPonderada ? 1 : 0) << endl;

    // Se os vértices forem ponderados, escreve os pesos
    if (verticePonderado) {
        for (int i = 0; i < numVertices; ++i) {
            arquivo << pesosVertices[i] << " ";  // Exemplo de impressão dos pesos dos vértices
        }
        arquivo << endl;
    }

    // Escreve as arestas, se existirem
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (matrizAdjacencia[i][j] != 0) {  // Se a aresta existir (não é 0)
                arquivo << i + 1 << " " << j + 1 << " " << matrizAdjacencia[i][j] << endl;
            }
        }
    }

    arquivo.close();
}

void GrafoMatriz::carregar_grafo(const std::string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo para leitura!" << endl;
        return;
    }

    int numVertices, direcionado, verticePonderado, arestaPonderada;
    arquivo >> numVertices >> direcionado >> verticePonderado >> arestaPonderada;

    // Inicializa a matriz de adjacência com base nas informações lidas
    this->numVertices = numVertices;
    this->direcionado = direcionado;
    this->verticePonderado = verticePonderado;
    this->arestaPonderada = arestaPonderada;

    // Recria a matriz de adjacência, caso necessário
    liberar_matriz();
    inicializar_matriz();

    // Se os vértices são ponderados, leia os pesos dos vértices
    if (verticePonderado) {
        for (int i = 0; i < numVertices; ++i) {
            int peso;
            arquivo >> peso;  // Lê o peso de cada vértice
            pesosVertices[i] = peso;  // Armazena o peso no vetor de pesos de vértices
        }
    }

    // Ler as arestas e seus pesos
    int origem, destino, peso;
    while (arquivo >> origem >> destino >> peso) {
        origem--;  // Ajusta para índice 0 (já que no arquivo os vértices começam de 1)
        destino--; // Ajusta para índice 0
        adicionar_aresta(origem, destino, peso);
    }

    arquivo.close();
}