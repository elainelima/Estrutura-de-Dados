#ifndef ORDENADOR_UNIVERSAL_HPP
#define ORDENADOR_UNIVERSAL_HPP
#include "vetor.hpp"
#include "ordenadores.hpp"

typedef struct entrada {
    double limiarCusto;
    double a;
    double b;
    double c;
    int tam;
    int seed;
} entrada_t;
float custo(double a, double b, double c, est *est);
int menorCusto(float *vet, int tam,  int passoMPS);
int  shuffleVector(int *vet, int size, int numShuffle);
void ordenadorUniversal(int * A, int tam, int minTamParticao, int limiarQuebras, int numeroQuebras, est *est);
int determinaLimiarParticao(int * A, int tam, float limiarCusto, double a, double b, double c, int seed, est *est);
int determinaLimiarQuebras(int * A, int tam, float limiarCusto, double a, double b, double c, est *est);
void calculaNovaFaixaParticao(int limParticao, int *minMPS, int *maxMPS, int *passoMPS);
void calculaNovaFaixaQuebra(int limQuebra, int *minLQ, int *maxLQ, int *passoLQ);
void simuladorOrdenador(int * A, int tam, float limiarCusto, double a, double b, double c,int seed, int breaks, est_t *est);

#endif // ORDENADOR_UNIVERSAL_HPP
