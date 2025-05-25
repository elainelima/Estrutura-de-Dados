#include <stdio.h>
#include <stdlib.h>
#include "../include/ordenadores.hpp"
#include "../include/vetor.hpp"
#include <sstream>
#include <iostream>

void insertionSort(int v[], int l, int r, est_t *est) {
    int i, j, key;
    inccalls(est,1);
    for (i = l + 1; i <= r; i++) {
        key = v[i];
        incmove(est, 1);
        j = i - 1;
        inccmp(est,1);
        while (j >= l && v[j] > key) {
            inccmp(est,1); 
            v[j+1] = v[j];
            incmove(est, 1);
            j--;
        }
        v[j+1] = key;
        incmove(est, 1);
    }
}
// median of 3 integers
int median (int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;  // a b 
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
}
void partition3(int *A, int l, int r, int *i, int *j, est_t *est) {
    *i = l;
    *j = r;
    int mid =  A[(*i + *j)/2];
    int left = A[*j];
    int right = A[*i];
    inccalls(est,1);
    int pivot_idx = median(mid, left, right);
    int pivot =  pivot_idx;
    // Choose the pivot as the middle element
    do {
        inccmp(est, 1);
        // Find element on left side that is greater than pivot
        while (A[*i] < pivot) {
            (*i)++;
            inccmp(est, 1);
        }
        // Find element on right side that is less than pivot
        while (A[*j] > pivot) {
            (*j)--;
            inccmp(est, 1);
        }
        // If we found a pair of elements to swap
        inccmp(est, 1);
        if (*i <= *j) {
            // Swap elements
            swap(&A[*i], &A[*j], est);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}
// quicksort with median of 3
void quickSort3(int * A, int l, int r, est_t *est) { 
    int i, j;
    inccalls(est,1);
    partition3(A, l, r, &i, &j, est);
    if (l < j ) {
        quickSort3(A, l, j, est);
    }
    if(i < r) {
        quickSort3(A, i, r, est);
    }
}  

void quickSort3Ins(int * A, int l, int r, int minTamParticao, est_t *est) { 
    // Define threshold for small partitions
    inccalls(est, 1);
    int i, j;
    partition3(A, l, r, &i, &j, est);
    //std::cout << minTamParticao << std::endl;
    if (l < j) {
        if (abs(j-l)  < minTamParticao) {
            insertionSort(A, l, j, est);
        }
        else  quickSort3Ins(A, l, j, minTamParticao, est);
    }
    if (i < r) {
       if (abs(r-i)  < minTamParticao) {
            insertionSort(A, i, r, est);
        }
        else  quickSort3Ins(A, i, r, minTamParticao, est);
    }
}
