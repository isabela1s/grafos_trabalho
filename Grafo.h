#ifndef GRAFO_H
#define GRAFO_H

#include <string>

class Grafo {
public:
    Grafo(int numVertices, bool direcionado, bool verticePonderado, bool arestaPonderada);
    virtual ~Grafo();

    virtual bool eh_bipartido() const = 0;
    virtual int n_conexo() const = 0;
    virtual int get_grau(int vertice) const = 0;
    virtual bool possui_ponte() const = 0;
    void novo_grafo(const std::string& nomeArquivo);

    virtual void carregar_grafo(const std::string& nomeArquivo) = 0;
    virtual void imprimir_grafo(const std::string& nomeArquivo) const = 0;

    int get_ordem() const;
    bool eh_direcionado() const;
    bool vertice_ponderado() const;
    bool aresta_ponderada() const;
    virtual bool eh_completo() const = 0;
    virtual bool eh_arvore() const = 0;
    virtual bool possui_articulacao() const = 0;

protected:
    int numVertices;
    int numArestas;
    bool direcionado;
    bool verticePonderado;
    bool arestaPonderada;
};

#endif // GRAFO_H