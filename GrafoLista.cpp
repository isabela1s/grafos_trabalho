#include "GrafoLista.h"
#include <fstream>
#include <iostream>

using namespace std;

GrafoLista::GrafoLista(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada)
    : Grafo(numVertices, direcionado, verticePonderado, arestaPonderada) {
        this->numVertices = numVertices;
        listaAdj = new ListaEncad[numVertices];
        pesosVertices = new int[numVertices];
}

GrafoLista::~GrafoLista() {
    delete[] listaAdj;
    delete[] pesosVertices;
}

void GrafoLista::carregar_grafo(const std::string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    if(!arquivo) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return;
    }

    arquivo >> numVertices >> direcionado >> verticePonderado >> arestaPonderada;

    // Liberar a memória alocada anteriormente
    delete[] listaAdj;
    delete[] pesosVertices;

    // Inicializar nova lista de adjacência e pesos de vértices
    listaAdj = new ListaEncad[numVertices];

    if(verticePonderado) {
        pesosVertices = new int[numVertices];
        for(int i = 0; i < numVertices; i++) {
            arquivo >> pesosVertices[i];
            //cout << "Peso do vértice " << i + 1 << ": " << pesosVertices[i] << endl;
        }
    } else {
        pesosVertices = nullptr;
    }

    int origem, destino, peso = 0;
    while (arquivo >> origem >> destino) {
        if (arestaPonderada) {
            arquivo >> peso;
            //cout << "Lendo aresta: origem=" << origem << ", destino=" << destino << ", peso=" << peso << endl;
        } else {
            peso = 1; // Peso padrão para arestas não ponderadas

            //cout << "Lendo aresta: origem=" << origem << ", destino=" << destino << ", peso=" << peso << endl;
        }
        adicionar_aresta(origem - 1, destino - 1, peso);
    }

    arquivo.close();
    cout << "Grafo carregado de " << nomeArquivo << std::endl;
}

void GrafoLista::adicionar_vertice(int id) {
    if (id >= numVertices) {
        cerr << "Erro: ID do vértice fora do limite." << endl;
        return;
    }
}

// void GrafoLista::imprimir_grafo(const string& nomeArquivo) const {
//     ofstream arquivo(nomeArquivo);
//     if (!arquivo.is_open()) {
//         cerr << "Erro ao abrir o arquivo para escrita." << endl;
//         return;
//     }

//     for (int i = 0; i < numVertices; i++) {
//         arquivo << "Vértice " << i + 1 << ": ";
//         //cout << "Processando vértice " << i + 1 << endl;

//         ListaEncad* lista = &listaAdj[i];
//         No* atual = lista->primeiro;
//         if (!atual) {
//             arquivo << "NULL";
//         }
//         while (atual) {
//             arquivo << atual->getInfo();
//             if (atual->getPeso() != -1) {
//                 arquivo << " (peso " << atual->getPeso() << ")";
//             }
//             if (atual->getProx()) {
//                 arquivo << " -> ";
//             }
//             atual = atual->getProx();
//         }

//         arquivo << endl;
//     }

//     arquivo.close();
//     cout << "Grafo salvo em " << nomeArquivo << endl;


// }

void GrafoLista::imprimir_grafo(const std::string& nomeArquivo) const {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo para escrita. " << endl;
        return;
    }

    int grau = numArestas;
    arquivo << "Grau: " << grau << endl;

    int ordem = numVertices;
    arquivo << "Ordem: " << ordem << endl;

    arquivo << "Direcionado: " << (direcionado ? "Sim" : "Não") << endl;

    arquivo << "Vertices ponderados: " << (verticePonderado ? "Sim" : "Não") << endl;

    arquivo << "Arestas ponderadas: " << (arestaPonderada ? "Sim" : "Não") << endl;

    bool completo = true;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i != j && !existe_aresta(i, j)) {
                completo = false;
                break;
            }
        }
        if (!completo) break;
    }
    arquivo << "Completo: " << (completo ? "Sim" : "Não") << endl;

    // Maior menor distância (Diâmetro do grafo)
    double maior_menor_distancia = calcular_diametro();
    arquivo << "Maior menor distância: " << maior_menor_distancia << endl;

    arquivo.close();
    std::cout << "Grafo salvo em " << nomeArquivo << endl;
}

double GrafoLista::calcular_diametro() const {
    const int INF = 1000000;
    int dist[numVertices][numVertices];

    // Inicializa a matriz de distâncias
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (existe_aresta(i, j)) {
                dist[i][j] = 1; 
            } else {
                dist[i][j] = INF;
            }
        }
    }

    for (int k = 0; k < numVertices; k++) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Encontrar o maior valor na matriz de distâncias
    double maxDist = 0;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (dist[i][j] != INF && dist[i][j] > maxDist) {
                maxDist = dist[i][j];
            }
        }
    }

    return maxDist;
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

    for (int i = 0; i < numVertices; i++) {
        listaAdj[i].removeNo(vertice + 1);
    }

    for (int i = vertice; i < numVertices - 1; i++) {
        listaAdj[i] = listaAdj[i + 1]; 
    }

    numVertices--;

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

void GrafoLista::novo_no(int id, int peso) {
    if (id >= numVertices) {
        cout << "ID do vértice fora do limite." << endl;
        return;
    }
    listaAdj[id].novo_no(id, peso);
}

void GrafoLista::nova_aresta(int origem, int destino, int peso) {
    if (origem >= numVertices || destino >= numVertices) {
        cout << "Vértice fora do limite." << endl;
        return;
    }
    No* origemNo = listaAdj[origem].novo_no(origem, 0); 
    listaAdj[origem].nova_aresta(origemNo, destino, peso);
}

void GrafoLista::deleta_no(int id) {
    if (id >= numVertices) {
        cout << "ID do vértice fora do limite." << endl;
        return;
    }
    listaAdj[id].deleta_no(id);
}

void GrafoLista::deleta_aresta(int origem, int destino) {
    if (origem >= numVertices || destino >= numVertices) {
        cout << "Vértice fora do limite." << endl;
        return;
    }
    listaAdj[origem].deleta_aresta(origem, destino);
}