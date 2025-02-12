#include "../include/GrafoLista.h"
#include "../include/GrafoMatriz.h"
#include <iostream>

using namespace std;

void imprimir_instrucao() {
    cout << "Uso do programa:" << endl;
    cout << "  main.out -d -m <arquivo_grafo>  # Descrever grafo com matriz" << endl;
    cout << "  main.out -d -l <arquivo_grafo>  # Descrever grafo com lista" << endl;
}

int main(int argc, char* argv[]) {

    if(argc < 3) {
        imprimir_instrucao();
        return 1;
    }

    string modo = argv[1];
    string estrutura = argv[2];

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
            //grafo.carregar_grafo(arquivo_grafo);
            grafo.novo_no();
            grafo.nova_aresta(4, 2, 3);
            grafo.deleta_no(2);
            grafo.deleta_aresta(1, 3);
            auto resultado = grafo.maior_menor_distancia();
            cout << "Maior menor distância: (" << resultado.first.first << "-" << resultado.first.second << ") " << resultado.second << endl;
            grafo.imprimir_grafo("grafo_matriz_teste.txt");


            //Testando algumas funções:
            cout << "Grau do vértice 0: " << grafo.get_grau(0) << endl;
            cout << "É bipartido? " << (grafo.eh_bipartido() ? "Sim" : "Não") << endl;
            cout << "Número de componentes conexos: " << grafo.n_conexo() << endl;
            cout << "Possui ponte? " << (grafo.possui_ponte() ? "Sim" : "Não") << endl;
            cout << "Possui articulação? " << (grafo.possui_articulacao() ? "Sim" : "Não") << endl;
            cout << "É completo? " << (grafo.eh_completo() ? "Sim" : "Não") << endl;
            cout << "É uma árvore? " << (grafo.eh_arvore() ? "Sim" : "Não") << endl;

        } else if(estrutura == "-l") {
            GrafoLista grafo(4, false, false, false);

            grafo.carregar_grafo(arquivo_grafo);  
            
            grafo.imprimir_grafo("grafo_lista_saida.txt");

            // Testando funções
            cout << "Número de componentes conexos: " << grafo.n_conexo() << endl;
            cout << "Grau do vértice 0: " << grafo.get_grau(0) << endl;
            cout << "O grafo é bipartido? " << (grafo.eh_bipartido() ? "Sim" : "Não") << endl;
            cout << "O grafo é completo? " << (grafo.eh_completo() ? "Sim" : "Não") << endl;
            cout << "O grafo é uma árvore? " << (grafo.eh_arvore() ? "Sim" : "Não") << endl;
            cout << "O grafo possui articulação? " << (grafo.possui_articulacao() ? "Sim" : "Não") << endl;
            cout << "O grafo possui ponte? " << (grafo.possui_ponte() ? "Sim" : "Não") << endl;
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
