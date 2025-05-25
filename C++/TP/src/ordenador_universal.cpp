#include <stdio.h>
#include <stdlib.h>
#include "../include/ordenador_universal.hpp"
#include "../include/ordenadores.hpp"
#include "../include/vetor.hpp"
#include <sstream>
#include <iostream>

void simuladorOrdenador(int * A, int tam, float limiarCusto, double a, double b, double c, int seed, int breaks, est_t *est) {
        int limParticao = determinaLimiarParticao(A, tam,limiarCusto,a,b,c,seed, est);
        std::cout << "nummps" << " "<< 6 << " " << "limParticao" <<" " <<limParticao << " " << "mpsdiff" << " " << 0 << std::endl;
        srand48(1);//inicia novamente a seed
        shuffleVector(A,tam,breaks);//embralha o vetor com a quantidade de quebras inicial
        int limiarQuebra = determinaLimiarQuebras(A, tam,limiarCusto,a,b,c,est);
        std::cout << "numlq" << " "<< 6 << " " << "limQuebras" <<" " <<limiarQuebra << " " << "lqdiff" << " " << 0 << std::endl;
}
int shuffleVector(int *vet, int size, int numShuffle){
    int p1 = 0, p2 = 0, temp;
    for (int t = 0; t < numShuffle; t++) {
        while (p1 == p2) {
            p1 = (int) (drand48() * size);
            p2 = (int) (drand48() * size);
        }
        temp = vet[p1];
        vet[p1] = vet[p2];
        vet[p2] = temp;
        p1 = p2 = 0;
    }
    return 0;
}
// // Função principal do Ordenador Universal
void ordenadorUniversal(int * A, int tam, int minTamParticao, int limiarQuebras, est_t *est) {
    int numeroQuebras = countBreaks(A, tam);
    if (numeroQuebras < limiarQuebras) {
        insertionSort(A, 0, tam-1, est);
    } else {
        if (tam > minTamParticao) {
            quickSort3(A, 0, tam,est);
        } else {
            insertionSort(A, 0, tam, est);
        }
   }
}
float custo(double a, double b, double c, est_t *est){
    float custo = a *  est->cmp  + b *  est->move + c *  est->calls;

    return custo;
}
int menorCusto(float *vet, int tam, int passoMPS) {
    float menor = vet[0]; // Assume que o primeiro é o menor
    int indice = 0, menorCusto=2;
    for (int i = 1; i < tam; i++) {
        if (vet[i] < menor) {
            menor = vet[i]; // Atualiza o menor valor
            indice = i;
        }
    }
    for (int numMPS =0; numMPS < indice; numMPS++){
        menorCusto +=passoMPS;
    }
    return menorCusto;
}
int determinaLimiarQuebras(int * A, int tam, float limiarCusto, double a, double b, double c, est_t *est) {
    int breaks = countBreaks(A,tam);
    int minLQ = 1;
    int maxLQ = breaks;
    int passoLQ = (maxLQ - minLQ)/5;
    int numMPS =0;
    int limQuebra =breaks;
    float custosQS[6];
    float custosIS[6];
    float custoTotalQS=0;
    float custoTotalIS=0;
    
    float lqdiff = custo(a, b, c, est);
    int inter =0;
    while (
       (numMPS <= 5) && (lqdiff>limiarCusto)
        ) {
        numMPS =0;
        std::cout <<"inter" << " "<< inter++<<  std::endl;
        iniciaEstatistica(est);
        for (int t = minLQ; t <= maxLQ; t += passoLQ) {
            
            srand48(1);//inicia novamente a seed
            shuffleVector(A,tam,breaks);//embralha o vetor com a quantidade de quebras inicial
            ordenadorUniversal(A, tam-1, tam ,t, est);
            custosQS[numMPS] = custo(a, b, c, est);
            custoTotalQS +=custosQS[numMPS];
            incost(est, custosQS[numMPS]);
            inmps(est, t);
            //imprime a estatistica
            std::cout << "qs" << " "
            << "lq" << " " 
            << t << " " 
            << "cost" << " "
            << est->cost <<  " " 
            << "cmp" << " "
            << est->cmp << " " 
            << "move" <<" " 
            << est->move << " "
            << "calls" << " "
            <<est->calls 
            << std::endl;
            insertionSort(A,0,tam-1,est);
            custosQS[numMPS] = custo(a, b, c, est);
            custoTotalQS +=custosQS[numMPS];
            incost(est, custosQS[numMPS]);
            inmps(est, t);
             //imprime a estatistica
            std::cout << "is" << " "
            << "lq" << " " 
            << t << " " 
            << "cost" << " "
            << est->cost <<  " " 
            << "cmp" << " "
            << est->cmp << " " 
            << "move" <<" " 
            << est->move << " "
            << "calls" << " "
            <<est->calls 
            << std::endl;
            numMPS++;
        }
        limQuebra = menorCusto(custosQS, 6,  passoLQ);
        calculaNovaFaixaQuebra(limQuebra, &minLQ, &maxLQ, &passoLQ);
        lqdiff = fabs(custosQS[0] - custosQS[numMPS]);
    }
    return  limQuebra;
}
int determinaLimiarParticao(int * A, int tam, float limiarCusto, double a, double b, double c, int seed,  est_t *est) {
    int minMPS = 2;
    int maxMPS = tam;
    int passoMPS = (maxMPS - minMPS)/5;
    int breaks =0;
    int numMPS =0;
    int limParticao =tam-1;
    float custos[6];
    float custoTotal=0;
    breaks = countBreaks(A,tam);
    float diffCusto = custo(a, b, c, est);
    int inter =0;
    while (
        (diffCusto > limiarCusto) && (numMPS <=5)
        ) {
        numMPS =0;
        std::cout <<"inter" << " "<< inter++<<  std::endl;
        iniciaEstatistica(est);
        for (int t = minMPS; t <= maxMPS; t += passoMPS) {
            srand48(1);//inicia novamente a seed
            shuffleVector(A,tam,breaks);//embralha o vetor com a quantidade de quebras inicial
            ordenadorUniversal(A, tam-1, t ,breaks, est);
            custos[numMPS] = custo(a, b, c, est);
            custoTotal +=custos[numMPS];
            incost(est, custos[numMPS]);
            inmps(est, t);
             //imprime a estatistica
            std::cout << "mps" << " "
            << est->mps << " " 
            << "cost" << " "
            << est->cost <<  " " 
            << "cmp" << " "
            << est->cmp << " " 
            << "move" <<" " 
            << est->move << " "
            << "calls" << " "
            <<est->calls 
            << std::endl;
            numMPS++;
        }
        limParticao = menorCusto(custos, 6,  passoMPS);
        calculaNovaFaixaParticao(limParticao, &minMPS, &maxMPS, &passoMPS);
        diffCusto = fabs(custos[0] - custos[numMPS]);
    }
    return  limParticao;
}
void calculaNovaFaixaParticao(int limParticao, int *minMPS, int *maxMPS, int *passoMPS) {
    int newMin, newMax, numMPS;
    int newPassoMPS;
    if (limParticao == 0) {
        newMin = 0;
        newMax = 2;
    } else if (limParticao == numMPS - 1) {
        newMin = numMPS - 3;
        newMax = numMPS - 1;
    } else {
        newMin = limParticao - 1;
        newMax = limParticao + 1;
    }
    minMPS = &newMin;
    maxMPS = &newMax;
    
    newPassoMPS = (int)(*maxMPS - *minMPS) / 5;
    if (newPassoMPS == 0) newPassoMPS++;
    passoMPS = &newPassoMPS;
}
void calculaNovaFaixaQuebra(int limQuebra, int *minLQ, int *maxLQ, int *passoLQ) {
    int newMin, newMax, numLQ;
    int newPassoLQ;
    if (limQuebra == 0) {
        newMin = 0;
        newMax = 2;
    } else if (limQuebra == numLQ - 1) {
        newMin = numLQ - 3;
        newMax = numLQ - 1;
    } else {
        newMin = limQuebra - 1;
        newMax = limQuebra + 1;
    }
    minLQ = &newMin;
    maxLQ = &newMax;
    
    newPassoLQ = (int)(*maxLQ - *minLQ) / 5;
    if (newPassoLQ == 0) newPassoLQ++;
    passoLQ = &newPassoLQ;
}


