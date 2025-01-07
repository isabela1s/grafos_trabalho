#include <iostream>
#include "GrafoMatriz.h"
#include "GrafoLista.h"

using namespace std;

int main() {
    // Testando com GrafoMatriz
    cout << "Carregando grafo com matriz de adjacência..." << endl;
    GrafoMatriz grafoMatriz(0, false, false, false); // Inicializa sem vértices
    grafoMatriz.imprimir_grafo("grafo_saida.txt");
    grafoMatriz.carregar_grafo("grafo.txt");

    cout << "O grafo é conexo? " << (grafoMatriz.eh_conexo() ? "Sim" : "Não") << endl;

    // Testando com GrafoLista
    cout << "\nCarregando grafo com lista de adjacência..." << endl;
    GrafoLista grafoLista;
    grafoLista.imprimir_grafo("grafo_saida.txt");
    grafoLista.carregar_grafo("grafo.txt");

    cout << "Número de componentes conexas: " << grafoLista.n_conexo() << endl;

    return 0;
}
