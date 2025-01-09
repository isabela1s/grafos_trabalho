## 1. Para compilar o projeto:

Execute o comando: 
```bash
    g++ -o main main.cpp GrafoLista.cpp GrafoMatriz.cpp Grafo.cpp -std=c++17 
```
## 2. Para executar no modo descrição:
    ### Lista: ./main -d -l grafo_teste.txt
    ### Matriz: ./main -d -m grafo_teste.txt

## 3. Para executar no modo aleatório:
    ### Lista: ./main -c -l config.txt saida_lista.txt
    ### Matriz: ./main -c -m config.txt saida_matriz.txt