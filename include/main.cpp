#include "GrafoLista.h"
#include "GrafoMatriz.h"
#include <iostream>
using namespace std;

int main() {
    GrafoMatriz grafo(4, false, false, false); // Inicializa o grafo com 4 vértices
    grafo.carregar_grafo("grafo_teste.txt");         // Carrega o grafo a partir do arquivo
    grafo.imprimir_grafo("grafo_matriz_teste.txt"); // Imprime o grafo para verificar
    //grafo.adicionar_aresta(0, 1);
    //grafo.adicionar_aresta(1, 2);
    //grafo.adicionar_aresta(2, 3);
    //grafo.adicionar_aresta(3, 0);

    //std::cout << "Grau do vértice 0: " << grafo.get_grau(0) << std::endl;
    //std::cout << "É bipartido? " << (grafo.eh_bipartido() ? "Sim" : "Não") << std::endl;
    //std::cout << "Número de componentes conexos: " << grafo.n_conexo() << std::endl;
    //std::cout << "Possui ponte? " << (grafo.possui_ponte() ? "Sim" : "Não") << std::endl;
    //std::cout << "Possui articulação? " << (grafo.possui_articulacao() ? "Sim" : "Não") << std::endl;
    //std::cout << "É completo? " << (grafo.eh_completo() ? "Sim" : "Não") << std::endl;
    //std::cout << "É uma árvore? " << (grafo.eh_arvore() ? "Sim" : "Não") << std::endl;
    return 0;
}
