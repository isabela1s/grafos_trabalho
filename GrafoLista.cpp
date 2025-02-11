#include "GrafoLista.h"
#include <fstream>
#include <iostream>

using namespace std;

GrafoLista::GrafoLista(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada)
    : Grafo(numVertices, direcionado, verticePonderado, arestaPonderada), listaAdj(nullptr) {
}

GrafoLista::~GrafoLista() {
    NoVertice* atual = listaAdj;
    while (atual) {
        Vertice* vertice = atual->vertice;
        Aresta* arestaAtual = vertice->arestas;

        while (arestaAtual) {
            Aresta* temp = arestaAtual;
            arestaAtual = arestaAtual->prox;
            delete temp;
        }

        delete vertice;
        NoVertice* tempVertice = atual;
        atual = atual->prox;
        delete tempVertice;
    }
}

void GrafoLista::adicionar_vertice(int id) {
    // Verifica se o vértice já existe
    NoVertice* atual = listaAdj;
    while (atual) {
        if (atual->vertice->id == id) {
            return;
        }
        atual = atual->prox;
    }

    // Criando novo vértice
    Vertice* novoVertice = new Vertice(id);
    NoVertice* novoNo = new NoVertice(novoVertice);

    // Encadeando na lista de adjacência
    novoNo->prox = listaAdj;
    listaAdj = novoNo;
    numVertices++;
}

void GrafoLista::imprimir_grafo(const std::string& nomeArquivo) const {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        return;
    }

    // Percorre todos os vértices da lista ligada
    NoVertice* atual = listaAdj;
    if (!atual) {
        std::cerr << "Lista de adjacência está vazia!" << std::endl;
    }

    while (atual) {
        int vertice = atual->vertice->id;
        arquivo << "Vértice " << vertice << ": ";
        std::cout << "Processando vértice " << vertice << std::endl;  // DEPURAÇÃO

        Aresta* aresta = atual->vertice->arestas;
        bool primeiraAresta = true;

        while (aresta) {
            if (!primeiraAresta) {
                arquivo << " ";
            }

            arquivo << aresta->destino;
            std::cout << " - Aresta para " << aresta->destino << " (peso: " << aresta->peso << ")" << std::endl; // DEPURAÇÃO

            if (aresta->peso != -1) {
                arquivo << " (peso " << aresta->peso << ")";
            }

            aresta = aresta->prox;
            primeiraAresta = false;
        }

        arquivo << std::endl;
        atual = atual->prox;
    }

    arquivo.close();
    std::cout << "Grafo salvo em " << nomeArquivo << std::endl;
}

int* GrafoLista::get_vizinhos(int vertice, int& tamanho) const {
    NoVertice* atual = listaAdj;

    while (atual) {
        if (atual->vertice->id == vertice) {
            Aresta* arestaAtual = atual->vertice->arestas;

            // Contar quantos vizinhos existem
            tamanho = 0;
            Aresta* temp = arestaAtual;
            while (temp) {
                tamanho++;
                temp = temp->prox;
            }

            // Criar array e armazenar vizinhos
            int* vizinhos = new int[tamanho];
            int i = 0;
            while (arestaAtual) {
                vizinhos[i++] = arestaAtual->destino;
                arestaAtual = arestaAtual->prox;
            }
            return vizinhos;
        }
        atual = atual->prox;
    }

    // Caso o vértice não seja encontrado, retorna nullptr
    tamanho = 0;
    return nullptr;
}

bool GrafoLista::existe_aresta(int origem, int destino) const {
    NoVertice* atual = listaAdj;

    while (atual) {
        if (atual->vertice->id == origem) {
            Aresta* aresta = atual->vertice->arestas;
            while (aresta) {
                if (aresta->destino == destino) {
                    return true;
                }
                aresta = aresta->prox;
            }
        }
        atual = atual->prox;
    }
    return false;
}

void GrafoLista::remover_vertice(int vertice) {
    NoVertice* atual = listaAdj;
    NoVertice* anterior = nullptr;

    // Remover todas as arestas que apontam para este vértice
    NoVertice* aux = listaAdj;
    while (aux) {
        remover_aresta(aux->vertice->id, vertice);
        aux = aux->prox;
    }

    // Remover o próprio vértice da lista de adjacência
    while (atual) {
        if (atual->vertice->id == vertice) {
            if (anterior) {
                anterior->prox = atual->prox;
            } else {
                listaAdj = atual->prox;
            }

            // Liberar memória das arestas
            Aresta* arestaAtual = atual->vertice->arestas;
            while (arestaAtual) {
                Aresta* temp = arestaAtual;
                arestaAtual = arestaAtual->prox;
                delete temp;
            }

            delete atual->vertice;
            delete atual;
            numVertices--;
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void GrafoLista::remover_aresta(int origem, int destino) {
    NoVertice* atual = listaAdj;

    while (atual) {
        if (atual->vertice->id == origem) {
            Aresta* arestaAtual = atual->vertice->arestas;
            Aresta* anterior = nullptr;

            while (arestaAtual) {
                if (arestaAtual->destino == destino) {
                    if (anterior) {
                        anterior->prox = arestaAtual->prox;
                    } else {
                        atual->vertice->arestas = arestaAtual->prox;
                    }
                    delete arestaAtual;
                    numArestas--;
                    return;
                }
                anterior = arestaAtual;
                arestaAtual = arestaAtual->prox;
            }
        }
        atual = atual->prox;
    }
}

bool GrafoLista::eh_vizinho(int u, int vizinho) const {
    NoVertice* atual = listaAdj;

    while (atual) {
        if (atual->vertice->id == u) {
            Aresta* aresta = atual->vertice->arestas;
            while (aresta) {
                if (aresta->destino == vizinho) {
                    return true;
                }
                aresta = aresta->prox;
            }
        }
        atual = atual->prox;
    }
    return false;
}

Grafo* GrafoLista::copia() const {
    GrafoLista* novoGrafo = new GrafoLista(numVertices, direcionado, verticePonderado, arestaPonderada);

    NoVertice* atual = listaAdj;
    while (atual) {
        novoGrafo->adicionar_vertice(atual->vertice->id);

        Aresta* arestaAtual = atual->vertice->arestas;
        while (arestaAtual) {
            novoGrafo->adicionar_aresta(atual->vertice->id, arestaAtual->destino, arestaAtual->peso);
            arestaAtual = arestaAtual->prox;
        }

        atual = atual->prox;
    }

    return novoGrafo;
}

void GrafoLista::adicionar_aresta(int origem, int destino, int peso) {
    NoVertice* atual = listaAdj;

    // Encontra o vértice de origem
    while (atual) {
        if (atual->vertice->id == origem) {
            // Cria nova aresta
            Aresta* novaAresta = new Aresta(destino, peso);
            novaAresta->prox = atual->vertice->arestas;
            atual->vertice->arestas = novaAresta;
            numArestas++;
            return;
        }
        atual = atual->prox;
    }
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

    delete[] vizinhos; // Libera a memória alocada
}


