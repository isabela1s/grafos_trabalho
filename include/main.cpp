#include "GrafoLista.h"
#include "GrafoMatriz.h"
#include <iostream>
using namespace std;

int main() {

    GrafoLista grafo(4, false, false, false);
    grafo.novo_grafo("config.txt");
    grafo.imprimir_grafo("grafo_impressao.txt");

    //GrafoMatriz grafo(4, false, false, false); // Inicializa o grafo com 4 vértices
    //grafo.carregar_grafo("grafo_teste.txt");         // Carrega o grafo a partir do arquivo
    //grafo.imprimir_grafo("grafo_matriz_teste.txt"); // Imprime o grafo para verificar

    // Testando algumas funções:
    //cout << "Grau do vértice 0: " << grafo.get_grau(0) << endl;
    //cout << "É bipartido? " << (grafo.eh_bipartido() ? "Sim" : "Não") << endl;
    //cout << "Número de componentes conexos: " << grafo.n_conexo() << endl;
    //cout << "Possui ponte? " << (grafo.possui_ponte() ? "Sim" : "Não") << endl;
    //cout << "Possui articulação? " << (grafo.possui_articulacao() ? "Sim" : "Não") << endl;
    //cout << "É completo? " << (grafo.eh_completo() ? "Sim" : "Não") << endl;
    //cout << "É uma árvore? " << (grafo.eh_arvore() ? "Sim" : "Não") << endl;

    // Adicionando vértices e arestas
    //grafo.adicionar_vertice(0);
    //grafo.adicionar_vertice(1);
    //grafo.adicionar_vertice(2);
    //grafo.adicionar_vertice(3);

    // Adicionando arestas
    //grafo.adicionar_aresta(0, 1); // Aresta entre 0 e 1
    //grafo.adicionar_aresta(1, 2); // Aresta entre 1 e 2
    //grafo.adicionar_aresta(2, 3); // Aresta entre 2 e 3
    //grafo.adicionar_aresta(3, 0); // Aresta entre 3 e 0

    // Testando funções
    //std::cout << "Número de componentes conexos: " << grafo.n_conexo() << std::endl;
    //std::cout << "Grau do vértice 0: " << grafo.get_grau(0) << std::endl;
    //std::cout << "O grafo é bipartido? " << (grafo.eh_bipartido() ? "Sim" : "Não") << std::endl;
    //std::cout << "O grafo é completo? " << (grafo.eh_completo() ? "Sim" : "Não") << std::endl;
    //std::cout << "O grafo é uma árvore? " << (grafo.eh_arvore() ? "Sim" : "Não") << std::endl;
    //std::cout << "O grafo possui articulação? " << (grafo.possui_articulacao() ? "Sim" : "Não") << std::endl;
    //std::cout << "O grafo possui ponte? " << (grafo.possui_ponte() ? "Sim" : "Não") << std::endl;

    // Imprimindo o grafo (caso você tenha implementado imprimir_grafo)
    //grafo.imprimir_grafo("grafo_impressao.txt");

    return 0;
}
