#include "GrafoLista.h"
#include "GrafoMatriz.h"
#include <iostream>
using namespace std;

void imprimir_instrucao() {
    cout << "Uso do programa:" << endl;
    cout << "  main.out -d -m <arquivo_grafo>  # Descrever grafo com matriz" << endl;
    cout << "  main.out -d -l <arquivo_grafo>  # Descrever grafo com lista" << endl;
    cout << "  main.out -c -m <arquivo_desc> <arquivo_saida>  # Criar grafo aleatório com matriz" << endl;
    cout << "  main.out -c -l <arquivo_desc> <arquivo_saida>  # Criar grafo aleatório com lista" << endl;
}

int main(int argc, char* argv[]) {

<<<<<<< HEAD
    // Testando funções
    cout << "Número de componentes conexos: " << grafo.n_conexo() << endl;
    cout << "Grau do vértice 0: " << grafo.get_grau(0) << endl;
    cout << "O grafo é bipartido? " << (grafo.eh_bipartido() ? "Sim" : "Não") << endl;
    cout << "O grafo é completo? " << (grafo.eh_completo() ? "Sim" : "Não") << endl;
    cout << "O grafo é uma árvore? " << (grafo.eh_arvore() ? "Sim" : "Não") << endl;
    cout << "O grafo possui articulação? " << (grafo.possui_articulacao() ? "Sim" : "Não") << endl;
    cout << "O grafo possui ponte? " << (grafo.possui_ponte() ? "Sim" : "Não") << endl;
    cout << "Número de componentes conexos: " << grafo.n_conexo() << endl;

    cout << "O grafo é bipartido? " << (grafo.eh_bipartido() ? "Sim" : "Não") << endl;
    cout << "O grafo é completo? " << (grafo.eh_completo() ? "Sim" : "Não") << endl;
    cout << "O grafo é uma árvore? " << (grafo.eh_arvore() ? "Sim" : "Não") << endl;
    cout << "O grafo possui articulação? " << (grafo.possui_articulacao() ? "Sim" : "Não") << endl;
    cout << "O grafo possui ponte? " << (grafo.possui_ponte() ? "Sim" : "Não") << endl;
    // Imprimindo o grafo (caso você tenha implementado imprimir_grafo)
    //grafo.imprimir_grafo("grafo_impressao.txt");
=======
    if(argc < 3) {
        imprimir_instrucao();
        return 1;
    }

    string modo = argv[1];
    string estrutura = argv[2];
>>>>>>> 569d15db7579c82387f7b708466ff3d566dd747f

    if(modo == "-d") {
        // Descrever
        if (argc != 4) {
            imprimir_instrucao();
            return 1;
        }

        string arquivo_grafo = argv[3];

        if(estrutura == "-m") {
            GrafoMatriz grafo(4, false, false, false); // Inicializa o grafo com 4 vértices
            grafo.carregar_grafo("grafo_teste.txt");         // Carrega o grafo a partir do arquivo
            grafo.imprimir_grafo("grafo_matriz_teste.txt"); // Imprime o grafo para verificar

            //Testando algumas funções:
            cout << "Grau do vértice 0: " << grafo.get_grau(0) << endl;
            cout << "É bipartido? " << (grafo.eh_bipartido() ? "Sim" : "Não") << endl;
            cout << "Número de componentes conexos: " << grafo.n_conexo() << endl;
            cout << "Possui ponte? " << (grafo.possui_ponte() ? "Sim" : "Não") << endl;
            cout << "Possui articulação? " << (grafo.possui_articulacao() ? "Sim" : "Não") << endl;
            cout << "É completo? " << (grafo.eh_completo() ? "Sim" : "Não") << endl;
            cout << "É uma árvore? " << (grafo.eh_arvore() ? "Sim" : "Não") << endl;

<<<<<<< HEAD
    // Testando funções
    //cout << "Número de componentes conexos: " << grafo.n_conexo() << endl;
    //cout << "Grau do vértice 0: " << grafo.get_grau(0) << endl;
    //cout << "O grafo é bipartido? " << (grafo.eh_bipartido() ? "Sim" : "Não") << endl;
    //cout << "O grafo é completo? " << (grafo.eh_completo() ? "Sim" : "Não") << endl;
    //cout << "O grafo é uma árvore? " << (grafo.eh_arvore() ? "Sim" : "Não") << endl;
    //cout << "O grafo possui articulação? " << (grafo.possui_articulacao() ? "Sim" : "Não") << endl;
    //cout << "O grafo possui ponte? " << (grafo.possui_ponte() ? "Sim" : "Não") << endl;
=======
        } else if(estrutura == "-l") {
            GrafoLista grafo(4, false, false, false);
>>>>>>> 569d15db7579c82387f7b708466ff3d566dd747f

            // Adicionando vértices e arestas
            grafo.adicionar_vertice(0);
            grafo.adicionar_vertice(1);
            grafo.adicionar_vertice(2);
            grafo.adicionar_vertice(3);

            // Adicionando arestas
            grafo.adicionar_aresta(0, 1); // Aresta entre 0 e 1
            grafo.adicionar_aresta(1, 2); // Aresta entre 1 e 2
            grafo.adicionar_aresta(2, 3); // Aresta entre 2 e 3
            grafo.adicionar_aresta(3, 0); // Aresta entre 3 e 0

            // Testando funções
            cout << "Número de componentes conexos: " << grafo.n_conexo() << std::endl;
            cout << "Grau do vértice 0: " << grafo.get_grau(0) << std::endl;
            cout << "O grafo é bipartido? " << (grafo.eh_bipartido() ? "Sim" : "Não") << std::endl;
            cout << "O grafo é completo? " << (grafo.eh_completo() ? "Sim" : "Não") << std::endl;
            cout << "O grafo é uma árvore? " << (grafo.eh_arvore() ? "Sim" : "Não") << std::endl;
            cout << "O grafo possui articulação? " << (grafo.possui_articulacao() ? "Sim" : "Não") << std::endl;
            cout << "O grafo possui ponte? " << (grafo.possui_ponte() ? "Sim" : "Não") << std::endl;

            // Imprimindo o grafo (caso você tenha implementado imprimir_grafo)
            grafo.imprimir_grafo("grafo_impressao.txt");
        } else {
            imprimir_instrucao();
            return 1;
        }

    } else if(modo == "-c") {
        // Criar aleatório
        if (argc != 5) {
            imprimir_instrucao();
            return 1;
        }

        string arquivo_desc = argv[3];
        string arquivo_saida = argv[4];

        if(estrutura == "-m") {
            GrafoMatriz grafo(4, false, false, false);

            grafo.novo_grafo("config.txt");
            grafo.imprimir_grafo("grafo_impressao.txt");
        } else if(estrutura == "-l") {
            GrafoLista grafo(4, false, false, false);

            grafo.novo_grafo("config.txt");
            grafo.imprimir_grafo("grafo_impressao.txt");
        } else {
            imprimir_instrucao();
            return 1;
        }

    } else {
        imprimir_instrucao();
        return 1;
    }

    return 0;
}
