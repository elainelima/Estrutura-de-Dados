#ifndef EVALENUM_HPP
#define EVALENUM_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <unistd.h>
#include <ctime>

// Algorithm identifiers
#define ALGINSERTION 1
#define ALGSELECTION 2
#define ALGQSORT     3
#define ALGQSORT3    4
#define ALGQSORTINS  5
#define ALGQSORT3INS 6
#define ALGSHELLSORT 7
#define ALGRECSEL    8

// Structures
typedef struct alg {
    int num;
    char *name;
} alg_t;

typedef struct opt {
    int size;
    int seed;
    int alg;
} opt_t;

typedef struct sortperf {
    int cmp;
    int move;
    int calls;
} sortperf_t;

// Functions
int name2num(char *name);
char *num2name(int num);
void resetcounter(sortperf_t *s);
void inccmp(sortperf_t *s, int num);
void incmove(sortperf_t *s, int num);
void inccalls(sortperf_t *s, int num);
char *printsortperf(sortperf_t *s, char *str, char *pref);
void initVector(int *vet, int size);
void printVector(int *vet, int size);
void swap(int *xp, int *yp, sortperf_t *s);
void shellSort(int *A, int n, sortperf_t *s);
void recursiveSelectionSort(int arr[], int l, int r, sortperf_t *s);
void selectionSort(int arr[], int l, int r, sortperf_t *s);
void insertionSort(int v[], int l, int r, sortperf_t *s);
int median(int a, int b, int c);
void partition3(int *A, int l, int r, int *i, int *j, sortperf_t *s);
void partition(int *A, int l, int r, int *i, int *j, sortperf_t *s);
void quickSort(int *A, int l, int r, sortperf_t *s);
void quickSort3(int *A, int l, int r, sortperf_t *s);
void quickSortIns(int *A, int l, int r, sortperf_t *s);
void quickSort3Ins(int *A, int l, int r, sortperf_t *s);
void uso();
void parse_args(int argc, char **argv, opt_t *opt);
void clkDiff(struct timespec t1, struct timespec t2, struct timespec *res);

#endif // EVALENUM_HPP
