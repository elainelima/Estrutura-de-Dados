#include "heap.hpp"
#include <sstream>
#include <iostream>

Heap::Heap(int maxsize) {
    tamanho = 0;
    data = new int[maxsize];
}

Heap::~Heap() {
    delete[] data;
}

void Heap::Inserir(int x) {
    data[tamanho] = x;
    HeapifyPorCima(tamanho);
    tamanho++;
}

int Heap::Remover() {
    int raiz = data[0];
    data[0] = data[tamanho - 1];
    tamanho--;
    HeapifyPorBaixo(0);
    return raiz;
}

bool Heap::Vazio() {
    return tamanho == 0;
}

int Heap::GetAncestral(int posicao) {
    return (posicao - 1) / 2;
}

int Heap::GetSucessorEsq(int posicao) {
    return 2 * posicao + 1;
}

int Heap::GetSucessorDir(int posicao) {
    return 2 * posicao + 2;
}

void Heap::HeapifyPorBaixo(int posicao) {
    int maior = posicao;
    int esquerdo = GetSucessorEsq(posicao);
    int direito = GetSucessorDir(posicao);

    if (esquerdo < tamanho && data[esquerdo] < data[maior]) {
        maior = esquerdo;
    }

    if (direito < tamanho && data[direito] < data[maior]) {
        maior = direito;
    }

    if (maior != posicao) {
        swap(&data[posicao], &data[maior]);
        HeapifyPorBaixo(maior);
    }
}

void Heap::HeapifyPorCima(int posicao) {
    int ancestral = GetAncestral(posicao);
    while (posicao > 0 && data[posicao] < data[ancestral]) {
        swap(&data[posicao], &data[ancestral]);
        posicao = ancestral;
        ancestral = GetAncestral(posicao);
    }
}
void Heap::swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
