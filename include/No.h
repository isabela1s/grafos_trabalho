#ifndef NO_H
#define NO_H

class No {
    public:
        No(int val, int p); // Construtor modificado
        ~No(); // Destrutor

        int getInfo();
        int getPeso(); // Novo método para obter o peso
        No* getProx();
        
        void setInfo(int val);
        void setPeso(int p); // Novo método para definir o peso
        void setProx(No *p);
        
    private:
        int info;
        int peso; // Novo atributo para armazenar o peso da aresta
        No *prox;
};

#endif
