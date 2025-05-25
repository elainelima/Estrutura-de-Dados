#ifndef ORDENADORES_HPP
#define ORDENADORES_HPP
#include "vetor.hpp"
#include "ordenador_universal.hpp"

void insertionSort(int v[], int l, int r, est_t *est);
int median(int a, int b, int c);
void partition3(int *A, int l, int r, int *i, int *j, est_t *est);
void quickSort3(int * A, int l, int r, est_t *est);
void quickSort3Ins(int * A, int l, int r, int minTamParticao, est_t *est);


#endif // ORDENADORES_HPP