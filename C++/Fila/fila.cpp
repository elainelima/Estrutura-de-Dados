#include <iostream>
class No{
    public:
        int valor;
        No *prox;
};
class Fila{
    public:
        Fila();
        ~Fila();
        int cont =0;
        void Insere(int valor);
        int Remove();
        bool Vazia();
        void Imprime();
    private:
        No *inicio;
        No *fim;
};

Fila::Fila(){
    inicio = NULL;
    fim = NULL;
};
void Fila::Insere(int valor){
    No *novo = new No();
    No *novoAnterior = fim;
    int cont=0;
    novo->valor = valor;
    if(inicio ==NULL && fim == NULL){
        inicio = novo;
        fim = novo;
    }
    else{
        novoAnterior->prox = novo;
        fim = novo;
    }
    cont++

}