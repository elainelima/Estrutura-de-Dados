#include <stdio.h>
#include <stdlib.h>
#include "../include/vetor.hpp"
#include <sstream>
#include <iostream>

void iniciaEstatistica(est_t *est) {
    est->cmp = 0;
    est->move = 0;
    est->calls = 0;
    est->cost = 0;
    est->mps = 0;
}

void inccmp(est_t *est, int num) {
    est->cmp += num;
}

void incmove(est_t *est, int num) {
    est->move += num;
}

void inccalls(est_t *est, int num) {
    est->calls += num;
}
void incost(est_t *est, float cost) {
    est->cost += cost;
}
void inmps(est_t *est, int mps) {
    est->mps = mps;
}

char *printsortperf(est_t *est, char *str, char *pref) {
    sprintf(str, "%s cmp %d move %d calls %d", pref, est->cmp, est->move, est->calls);
    return str;
}

void initVector(int *vet, int size) {
    for (int i = 0; i < size; i++) {
        vet[i] = (int)(drand48() * size);
    }
}

void printVector(int *vet, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void swap(int *xp, int *yp, est_t *est) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
    incmove(est, 3);
}
int countBreaks(int *vet, int tam) {//funcao para contar a quantidade de breaks de um vetor
    int count = 0;
    for (int i = 1; i < tam; ++i) {
        if (vet[i] < vet[i - 1]) {
            count++; 
        }
    }
    return count;
}
