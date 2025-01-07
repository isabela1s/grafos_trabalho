#include "GrafoLista.h"
# include <fstream>

using namespace std;

Aresta::Aresta(int destino) {
  this->destino = destino;
  this->prox = nullptr;
}

Vertice::Vertice(int id) {
  this->id = id;
  this->arestas = nullptr;
  this->prox = nullptr;
}

void Vertice::adicionaAresta(int destino) {
  Aresta* newAresta = new Aresta(destino);
  newAresta->prox = this->arestas;
  this->arestas = newAresta;
}

//GrafoLista::GrafoLista() {
  //this->vertices = nullptr;
//}
GrafoLista::GrafoLista() : Grafo(0, false, false, false) {
    vertices = nullptr;
}


GrafoLista::~GrafoLista() {
  Vertice* vTemp = this->vertices;
  while (vTemp != nullptr) {
    Aresta* aTemp = vTemp->arestas;
    while (aTemp != nullptr) {
      Aresta* newAresta = aTemp;
      aTemp = aTemp->prox;
      delete newAresta;
    }
    Vertice* newVertice = vTemp;
    vTemp = vTemp->prox;
    delete newVertice;
  }
}
void GrafoLista::addVertice(int id) {
  Vertice* newVertice = new Vertice(id);
  newVertice->prox = this->vertices;
  this->vertices = newVertice;
}

void GrafoLista::addAresta(int origem, int destino) {
  Vertice* vAtual = this->vertices;
  while (vAtual != nullptr) {
    if (vAtual->id == origem) {
      vAtual->adicionaAresta(destino);
      return;
    }
    vAtual = vAtual->prox;
  }

  addVertice(origem);
  vertices->adicionaAresta(destino);
}

void GrafoLista::imprimir_grafo(const string& nomeArquivo) {
    ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return;
    }

    Vertice* vAtual = vertices;
    while (vAtual) {
        arquivo << "Vértice " << vAtual->id << " : ";
        Aresta* aAtual = vAtual->arestas;
        while (aAtual) {
            arquivo << " -> " << aAtual->destino;
            aAtual = aAtual->prox;
        }
        arquivo << "\n";
        vAtual = vAtual->prox;
    }

    arquivo.close();
}

bool GrafoLista::eh_conexo()
{
    bool* verticeVisitado = new bool[getNumVertices()];
    for (int i = 0; i < getNumVertices(); ++i)
      verticeVisitado[i] = false;

    Vertice* verticeAtual = this->vertices;

    dfs(verticeAtual, verticeVisitado);

    for (int i = 0; i < getNumVertices(); ++i)
    {
      if (!verticeVisitado[i])
      {
        delete[] verticeVisitado;
        return false;
      }
    }

    delete[] verticeVisitado;
    return true;
}

void GrafoLista::dfs(Vertice* vertice, bool verticeVisitado[])
{
  verticeVisitado[vertice->id] = true;

  Aresta* arestaAtual = vertice->arestas;
  while (arestaAtual != nullptr)
  {
    if (!verticeVisitado[arestaAtual->destino])
      dfs(getVertice(arestaAtual->destino), verticeVisitado);

    arestaAtual = arestaAtual->prox;
  }
}

int GrafoLista::getNumVertices()
{
  int count = 0;
  Vertice* verticeAtual = this->vertices;
  while (verticeAtual != nullptr)
  {
    count++;
    verticeAtual = verticeAtual->prox;
  }
  return count;
}

Vertice* GrafoLista::getVertice(int id)
{
  Vertice* verticeAtual = this->vertices;
  while (verticeAtual != nullptr)
  {
    if (verticeAtual->id == id)
      return verticeAtual;

    verticeAtual = verticeAtual->prox;
  }
  return nullptr;
}

int GrafoLista::n_conexo()
{
  if (eh_conexo())
    return 1;

  bool* verticeVisitado = new bool[numVertices];
  int quantComponentesConexas = 0;

  for (int i = 0; i < numVertices; ++i)
    verticeVisitado[i] = false;

  for (int i = 0; i < numVertices; ++i)
  {
    Vertice* vertice = getVertice(i);
    if (vertice != nullptr && !verticeVisitado[vertice->id])
    {
      dfs(vertice, verticeVisitado);
      quantComponentesConexas++;
    }
  }

  delete[] verticeVisitado;
  return quantComponentesConexas;
}

bool GrafoLista::eh_bipartido()
{
  int totalCombinacoes = 1;
  for (int i = 0; i < numVertices; ++i)
  {
    totalCombinacoes *= 2; // Total de combinações é 2 elevado ao numVertices
  }

  int* conjunto = new int[numVertices];

  for (int combinacao = 0; combinacao < totalCombinacoes; ++combinacao)
  {
    for (int i = 0; i < numVertices; ++i)
    {
      if ((combinacao % (1 << (i + 1))) >= (1 << i))
      {
        conjunto[i] = 1;  // Marca como conjunto 1
      }
      else
      {
        conjunto[i] = 2;  // Marca como conjunto 2
      }
    }

    bool valido = true;
    for (int i = 0; i < numVertices; ++i)
    {
      Vertice* vertice = getVertice(i);
      Aresta* aresta = vertice->arestas;
      while (aresta != nullptr)
      {
        if (conjunto[vertice->id] == conjunto[aresta->destino])
        {
          valido = false;
          break;
        }
        aresta = aresta->prox;
      }
      if (!valido) break;
    }

    if (valido)
    {
      delete[] conjunto;
      return true;
    }
  }

  delete[] conjunto;
  return false;
}

int GrafoLista::get_grau()
{
  int grau = 0;

  for (int i = 0; i < numVertices; ++i)
  {
    Vertice* vertice = getVertice(i);
    Aresta* aresta = vertice->arestas;

    while (aresta != nullptr)
    {
      if (direcionado)
      {
        grau += 1;
      }
      else
      {
        if (aresta->destino == vertice->id)
        {
          grau += 1;
        }
        else
        {
          grau += 2;
        }
      }
      aresta = aresta->prox;
    }
  }

  if (!direcionado)
    grau /= 2;

  return grau;
}

bool GrafoLista::possui_ponte()
 {
  for (int u = 0; u < numVertices; ++u)
  {
    Vertice* vertice = getVertice(u);
    Aresta* aresta = vertice->arestas;

    while (aresta != nullptr)
    {
      int v = aresta->destino;

      aresta = aresta->prox;

      bool* verticeVisitado = new bool[numVertices];
      for (int i = 0; i < numVertices; ++i)
        verticeVisitado[i] = false;

      dfs(getVertice(0), verticeVisitado);

      bool ehConectado = true;
      for (int i = 0; i < numVertices; ++i)
      {
        if (!verticeVisitado[i])
        {
          ehConectado = false;
          break;
        }
      }

      if (!ehConectado)
      {
        delete[] verticeVisitado;
        return true; // (u, v) é ponte
      }

      delete[] verticeVisitado;
    }
  }

  return false; // não tem ponte
}

bool GrafoLista::possui_articulacao() {
    Vertice* vAtual = vertices;
    while (vAtual != nullptr) {
        int id = vAtual->id;

        // Remover temporariamente as arestas do vértice
        Aresta* backup = vAtual->arestas;
        vAtual->arestas = nullptr;

        // Verificar se o grafo ainda é conexo
        bool conexo = eh_conexo();

        // Restaurar as arestas
        vAtual->arestas = backup;

        // Se o grafo não for conexo, então v é uma articulação
        if (!conexo) {
            return true;
        }

        vAtual = vAtual->prox;
    }
    return false; // Nenhuma articulação encontrada
}
void GrafoLista::carregar_grafo(const std::string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return;
    }

    int numVertices, numArestas;
    arquivo >> numVertices >> numArestas;

    // Adiciona os vértices
    for (int i = 1; i <= numVertices; ++i) {
        addVertice(i);
    }

    int origem, destino;
    while (arquivo >> origem >> destino) {
        addAresta(origem, destino); // Adiciona aresta
    }

    arquivo.close();
}
