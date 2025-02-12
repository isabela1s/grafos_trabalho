#include "GrafoMatriz.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <queue>

using namespace std;

// Construtor
GrafoMatriz::GrafoMatriz(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada)
    : Grafo(numVertices, direcionado, verticePonderado, arestaPonderada) {

    // Inicializa a matriz de adjacência com 0 usando vectors
    matrizAdj.resize(numVertices, std::vector<int>(numVertices, 0));
}

// Destrutor
GrafoMatriz::~GrafoMatriz() {}

// Redimensiona a matriz quando o limite de vértices é atingido
void GrafoMatriz::redimensionar_matriz() {
    int novaCapacidade = capacidade * 2;

    // Redimensiona o número de linhas
    matrizAdj.resize(novaCapacidade);
    for (int i = 0; i < novaCapacidade; i++) {
        // Redimensiona as colunas em cada linha
        matrizAdj[i].resize(novaCapacidade, 0);
    }

    capacidade = novaCapacidade;
}

// Adiciona um novo vértice ao grafo
void GrafoMatriz::novo_no() {
    if (numVertices == capacidade) {
        redimensionar_matriz();
    }

    // Inicializa a nova linha e coluna
    for (int i = 0; i <= numVertices; ++i) {
        matrizAdj[i][numVertices] = 0;
        matrizAdj[numVertices][i] = 0;
    }

    numVertices++;
}


// Adiciona uma nova aresta
void GrafoMatriz::nova_aresta(int origem, int destino, int peso) {
    if (origem < numVertices && destino < numVertices) {
        matrizAdj[origem][destino] = peso;
        if (!direcionado) {
            matrizAdj[destino][origem] = peso;
        }
    } else {
        cout << "Erro: índice fora dos limites!\n";
    }
}

// Remove um vértice e ajusta a matriz
void GrafoMatriz::deleta_no(int no) {
    for (int i = no; i < numVertices - 1; i++) {
        for (int j = 0; j < numVertices; j++) {
            matrizAdj[i][j] = matrizAdj[i + 1][j];  // Desloca linhas
            matrizAdj[j][i] = matrizAdj[j][i + 1];  // Desloca colunas
        }
    }
    numVertices--;
}

// Remove uma aresta
void GrafoMatriz::deleta_aresta(int origem, int destino) {
    if (origem < numVertices && destino < numVertices) {
        matrizAdj[origem][destino] = 0;
        if (!direcionado) {
            matrizAdj[destino][origem] = 0;
        }
    }
}

// Carrega o grafo de um arquivo
void GrafoMatriz::carregar_grafo(const string& nomeArquivo) {
    cout << "Tentando abrir o arquivo: " << nomeArquivo << endl;
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
        return;
    }
    cout << "Arquivo aberto com sucesso!\n";
    int numVerticesArquivo;
    arquivo >> numVerticesArquivo;

    cout << "Número de vértices lido: " << numVerticesArquivo << endl;

    if (numVerticesArquivo != numVertices) {
        cerr << "Número de vértices no arquivo não corresponde ao grafo." << endl;
        return;
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            arquivo >> matrizAdj[i][j];
            cout << "matrizAdj[" << i << "][" << j << "] = " << matrizAdj[i][j] << endl;
        }
    }

    arquivo.close();
}
// Imprime o grafo em um arquivo
void GrafoMatriz::imprimir_grafo(const string& nomeArquivo) const {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
        return;
    }

    cout << "Matriz de Adjacência atual:\n";  // Imprime diretamente no console para depuração
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            arquivo << matrizAdj[i][j] << " ";
            cout << matrizAdj[i][j] << " ";  // Depuração no console
        }
        arquivo << endl;
        cout << endl;
    }

    arquivo.close();
    cout << "Matriz salva em " << nomeArquivo << endl;
}
// DFS para encontrar componentes conexos
void GrafoMatriz::dfs(int vertice, vector<bool>& visitados, const vector<vector<int>>& matriz) const {
    visitados[vertice] = true;
    for (int i = 0; i < numVertices; ++i) {
        if (matriz[vertice][i] != 0 && !visitados[i]) { // Verifica aresta e não visitado
            dfs(i, visitados, matriz); // Chamada recursiva
        }
    }
}
void GrafoMatriz::dfs(int vertice, vector<bool>& visitados) const {
    visitados[vertice] = true;
    for (int i = 0; i < numVertices; ++i) {
        if (matrizAdj[vertice][i] != 0 && !visitados[i]) { // Verifica aresta e não visitado
            dfs(i, visitados); // Chamada recursiva
        }
    }
}

int GrafoMatriz::get_ordem() const {
    return numVertices;
}

bool GrafoMatriz::eh_direcionado() const {
    return direcionado;
}

bool GrafoMatriz::vertice_ponderado() const {
    return verticePonderado;
}

bool GrafoMatriz::aresta_ponderada() const {
    return arestaPonderada;
}

bool GrafoMatriz::eh_bipartido() const {
    vector<int> cores(numVertices, -1); // -1 = Não colorido
    queue<int> fila;

    for (int i = 0; i < numVertices; ++i) {
        if (cores[i] == -1) { // Não visitado
            cores[i] = 0; // Primeira cor
            fila.push(i);

            while (!fila.empty()) {
                int vertice = fila.front();
                fila.pop();

                for (int j = 0; j < numVertices; ++j) {
                    if (matrizAdj[vertice][j] != 0) { // Aresta existe
                        if (cores[j] == -1) { // Não colorido
                            cores[j] = 1 - cores[vertice]; // Alterna cor
                            fila.push(j);
                        } else if (cores[j] == cores[vertice]) {
                            return false; // Não é bipartido
                        }
                    }
                }
            }
        }
    }
    return true; // É bipartido
}

int GrafoMatriz::n_conexo() const {
    vector<bool> visitados(numVertices, false);
    int componentes = 0;

    for (int i = 0; i < numVertices; ++i) {
        if (!visitados[i]) {
            componentes++;
            dfs(i, visitados); // Chama a versão de 2 parâmetros
        }
    }

    return componentes;
}
int GrafoMatriz::get_grau(int vertice) const {
    int grau = 0;
    for (int i = 0; i < numVertices; ++i) {
        if (matrizAdj[vertice][i] != 0) { // Conta as arestas conectadas
            grau++;
        }
    }
    return grau;
}


bool GrafoMatriz::possui_ponte() const {
    // Número de componentes conexos no grafo original
    int componentesOriginais = n_conexo();

    // Cria uma cópia da matriz de adjacência
    auto matrizCopia = matrizAdj;

    for (int u = 0; u < numVertices; ++u) {
        for (int v = 0; v < numVertices; ++v) {
            if (matrizCopia[u][v] != 0) { // Existe aresta (u, v)
                // Remove temporariamente a aresta (u, v)
                int pesoBackup = matrizCopia[u][v];
                matrizCopia[u][v] = 0;
                if (!direcionado) {
                    matrizCopia[v][u] = 0;
                }

                // Recalcula o número de componentes conexos com a cópia
                int novosComponentes = n_conexo();

                // Restaura a aresta (u, v)
                matrizCopia[u][v] = pesoBackup;
                if (!direcionado) {
                    matrizCopia[v][u] = pesoBackup;
                }

                // Verifica se o número de componentes aumentou
                if (novosComponentes > componentesOriginais) {
                    return true; // Encontrou uma ponte
                }
            }
        }
    }

    return false; // Nenhuma ponte encontrada
}

bool GrafoMatriz::possui_articulacao() const {
    int componentesOriginais = n_conexo();

    for (int v = 0; v < numVertices; ++v) {
        auto matrizCopia = matrizAdj;

        // Remove temporariamente o vértice v
        for (int u = 0; u < numVertices; ++u) {
            matrizCopia[v][u] = 0;
            matrizCopia[u][v] = 0;
        }

        int novosComponentes = 0;
        vector<bool> visitados(numVertices, false);
        for (int i = 0; i < numVertices; ++i) {
            if (!visitados[i]) {
                novosComponentes++;
                dfs(i, visitados, matrizCopia); // Chama a versão de 3 parâmetros
            }
        }

        if (novosComponentes > componentesOriginais) {
            return true; // Ponto de articulação encontrado
        }
    }

    return false; // Nenhum ponto de articulação encontrado
}

bool GrafoMatriz::eh_completo() const {
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            // Ignora a diagonal, pois um vértice não está conectado a si mesmo
            if (i != j && matrizAdj[i][j] == 0) {
                return false; // Se alguma aresta estiver faltando, o grafo não é completo
            }
        }
    }
    return true; // O grafo é completo
}

bool GrafoMatriz::eh_arvore() const {
    return (n_conexo() == 1) && (numArestas == numVertices - 1);
}
int GrafoMatriz::menor_distancia(int origem, int destino) {
    std::vector<int> dist(numVertices, INT_MAX);
    std::vector<bool> visitado(numVertices, false);
    dist[origem] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> fila;
    fila.push({0, origem});

    while (!fila.empty()) {
        int u = fila.top().second;
        fila.pop();

        if (visitado[u]) continue;
        visitado[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (matrizAdj[u][v] > 0 && !visitado[v]) {
                int novaDist = dist[u] + matrizAdj[u][v];
                if (novaDist < dist[v]) {
                    dist[v] = novaDist;
                    fila.push({dist[v], v});
                }
            }
        }
    }

    return dist[destino] == INT_MAX ? -1 : dist[destino];
}

std::pair<std::pair<int, int>, int> GrafoMatriz::maior_menor_distancia() {
    int maxDistancia = 0;
    std::pair<int, int> parMax;

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i != j) {
                int dist = menor_distancia(i, j);
                if (dist > maxDistancia) {
                    maxDistancia = dist;
                    parMax = {i, j};
                }
            }
        }
    }

    return {parMax, maxDistancia};
}