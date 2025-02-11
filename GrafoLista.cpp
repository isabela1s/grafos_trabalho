#include "GrafoLista.h"
#include <fstream>
#include <iostream>

using namespace std;

GrafoLista::GrafoLista(const char* nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    if(!arquivo) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        exit(1);
    }

    arquivo >> numVertices >> direcionado >> verticePonderado >> arestaPonderada;

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
        }
        insereAresta(origem - 1, destino - 1, peso);
    }

    arquivo.close();

}

GrafoLista::~GrafoLista() {
    delete [] listaAdj;
    if(arestaPonderada) {
        delete [] pesosVertices;
    }
}

void GrafoLista::insereAresta(int origem, int destino, int peso) {
    listaAdj[origem].insere(destino, peso); 
    
    if (!direcionado) {
        listaAdj[destino].insere(origem, peso);
    }
}
void GrafoLista::imprimeGrafo() {
    cout << "Grafo " << (direcionado ? "Direcionado" : "Não Direcionado") << endl;
    cout << "Número de Vértices: " << numVertices << endl;

    if (verticePonderado) {
        cout << "Pesos dos Vértices: ";
        for (int i = 0; i < numVertices; i++) {
            cout << pesosVertices[i] << " ";
        }
        cout << endl;
    }

    cout << "Lista de Adjacência:" << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << "Vértice " << (i + 1) << " -> ";
        listaAdj[i].imprimeLista();
        cout << endl;
    }
}

void GrafoLista::get_adjacentes(int v, int adjacentes[], int &size) const {
    listaAdj[v].get_adj(adjacentes, size);
}