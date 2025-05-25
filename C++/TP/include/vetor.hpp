#ifndef VETOR_HPP
#define VETOR_HPP

typedef struct est {
    int cmp;
    int move;
    int calls;
    float cost;
    int mps;
} est_t;
void iniciaEstatistica(est_t *est);
void inccmp(est_t *est, int num);
void incmove(est_t *est, int num);
void inccalls(est_t *est, int num);
void incost(est_t *est, float cost);
void inmps(est_t *est, int mps);
void initVector(int *vet, int size);//inicializa um vetor
void printVector(int *vet, int size);
void swap(int *xp, int *yp, est_t *est);//realiza as trocas do vetor
void resetcounter(est_t *est);
int countBreaks(int *vet, int tam);//funcao para contar a quantidade de breaks de um vetor
#endif 