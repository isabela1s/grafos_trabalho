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

void GrafoMatriz::imprimir_grafo(const std::string& nomeArquivo) {
    ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return;
    }

    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            arquivo << matrizAdjacencia[i][j] << " ";
        }
        arquivo << "\n";
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

bool GrafoMatriz::possui_articulacao() {
    for (int v = 0; v < numVertices; ++v) {
        // Remover temporariamente o vértice v
        int* backup = new int[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            backup[i] = matrizAdjacencia[v][i]; // Salvar a linha
            matrizAdjacencia[v][i] = 0;         // Remover as conexões
            matrizAdjacencia[i][v] = 0;         // Remover conexões de volta
        }

        // Verificar se o grafo ainda é conexo
        bool conexo = eh_conexo();

        // Restaurar as conexões
        for (int i = 0; i < numVertices; ++i) {
            matrizAdjacencia[v][i] = backup[i];
            matrizAdjacencia[i][v] = backup[i];
        }

        delete[] backup;

        // Se o grafo não for conexo, então v é uma articulação
        if (!conexo) {
            return true;
        }
    }
    return false; // Nenhuma articulação encontrada
}

