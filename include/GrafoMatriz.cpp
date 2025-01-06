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

bool GrafoMatriz::eh_conexo() 
{
    bool* verticeVisitado = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) 
    verticeVisitado[i] = false;

    dfs(0, verticeVisitado);

    for (int i = 0; i < numVertices; ++i) 
    {
        if (!verticeVisitado[i]) 
        {
            delete[] verticeVisitado;
            return false;
        }
    }

    delete[] verticeVisitado;
    return true;
}

void GrafoMatriz::dfs(int vertice, bool verticeVisitado[]) 
{
    verticeVisitado[vertice] = true;

    for (int i = 0; i < numVertices; ++i) {
        if (matrizAdjacencia[vertice][i] != 0 && !verticeVisitado[i]) {
            dfs(i, verticeVisitado);
        }
    }
}

int GrafoMatriz::n_conexo() 
{
    int quantComponentesConexas = 0;
    if (eh_conexo()) 
        return 1; 

    bool* verticeVisitado = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) 
        verticeVisitado[i] = false;

    for (int i = 0; i < numVertices; ++i) 
    {
        if (!verticeVisitado[i]) 
        {
            dfs(i, verticeVisitado);
            quantComponentesConexas++;
        }
    }

    delete[] verticeVisitado;
    return quantComponentesConexas;
}

bool GrafoMatriz::eh_bipartido() 
{
    int totalCombinacoes = 1;
    for (int i = 0; i < numVertices; ++i) 
    {
        totalCombinacoes *= 2; // Total de combinações é 2 elevado ao numVertices
    }    

    int* conjunto = new int[numVertices];    

    for (int combinacao = 0; combinacao < totalCombinacoes; ++combinacao) 
    {
        for (int i = 0; i < numVertices; ++i) 
        {
            conjunto[i] = (combinacao & (1 << i)) ? 1 : 2;
        }

        bool valido = true;
        for (int i = 0; i < numVertices; ++i) 
        {
            for (int j = 0; j < numVertices; ++j) 
            {
                if (matrizAdjacencia[i][j] != 0 && conjunto[i] == conjunto[j]) 
                {
                    valido = false;
                    break;
                }
            }
            if (!valido) break;
        }

        if (valido) 
        {
            delete[] conjunto;
            return true;
        }
    }

    delete[] conjunto;
    return false;
}

int GrafoMatriz::get_grau() 
{
    int grau = 0;

    for (int i = 0; i < numVertices; ++i) 
    {
        for (int j = 0; j < numVertices; ++j) 
        {
            if (matrizAdjacencia[i][j] != 0) 
            {
                if (direcionado) 
                {
                    grau += 1;
                } 
                else 
                {
                    if (i == j) 
                    {
                        grau += 1;
                    } 
                    else 
                    {
                        grau += 2;
                    }
                }
            }
        }
    }

    if (!direcionado) 
        grau /= 2; 

    return grau;
}

bool GrafoMatriz::possui_ponte() 
{
    // para cada aresta (i, j) que existe (peso diferente de 0), o código verifica se ela é uma ponte
    // a aresta é removida temporariamente e, no final, o valor original é restaurado (valorOriginal)
    for (int i = 0; i < numVertices; ++i) 
    {
        for (int j = 0; j < numVertices; ++j) 
        {
            if (matrizAdjacencia[i][j] != 0) 
            {
                int valorOriginal = matrizAdjacencia[i][j];
                matrizAdjacencia[i][j] = 0;
                if (!direcionado) 
                {
                    matrizAdjacencia[j][i] = 0;
                }

                bool* verticeVisitado = new bool[numVertices];
                for (int k = 0; k < numVertices; ++k) 
                {
                    verticeVisitado[k] = false;
                }
                dfs(0, verticeVisitado);

                for (int k = 0; k < numVertices; ++k) 
                {
                    if (!verticeVisitado[k]) 
                    {
                        matrizAdjacencia[i][j] = valorOriginal;
                        if (!direcionado) 
                        {
                            matrizAdjacencia[j][i] = valorOriginal;
                        }
                        delete[] verticeVisitado;
                        return true; // (i, j) é ponte
                    }
                }

                matrizAdjacencia[i][j] = valorOriginal;
                if (!direcionado) 
                {
                    matrizAdjacencia[j][i] = valorOriginal;
                }
                delete[] verticeVisitado;
            }
        }
    }
    return false; // não tem ponte
}
