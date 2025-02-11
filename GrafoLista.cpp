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

    arquivo >> numVertices >> direcionado >> verticePonderado >> arestaPonderada;
    cout << "numVertices: " << numVertices << ", direcionado: " << direcionado
         << ", verticePonderado: " << verticePonderado << ", arestaPonderada: " << arestaPonderada << endl;

    // Liberar a memória alocada anteriormente, se houver
    delete[] listaAdj;
    delete[] pesosVertices;

    // Inicializar nova lista de adjacência e pesos de vértices, se necessário
    listaAdj = new ListaEncad[numVertices];

    if(verticePonderado) {
        pesosVertices = new int[numVertices];
        for(int i = 0; i < numVertices; i++) {
            arquivo >> pesosVertices[i];
        }
    } else {
        pesosVertices = nullptr;
    }

    int origem, destino, peso = 0;
    while (arquivo >> origem >> destino) {
        if (arestaPonderada) {
            arquivo >> peso;
        } else {
            peso = 1; // Peso padrão para arestas não ponderadas
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
