#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "../include/ordenador_universal.hpp"
#include "../include/ordenadores.hpp"
#include "../include/vetor.hpp"
#include <sstream>

int main (int argc, char ** argv){
    int * vet;
    int breaks = 0;
    est est;
    entrada entrada;
    iniciaEstatistica(&est);

    std::string line;
    
    std::cin >> entrada.seed;
    std::cin >> entrada.limiarCusto;
    std::cin >> entrada.a;
    std::cin >> entrada.b;
    std::cin >> entrada.c;
    std::cin >> entrada.tam;

    // malloc with opt.size+1 for heapsort
    vet = (int *) malloc((entrada.tam));

    // initialize
    iniciaEstatistica(&est);//zera as estatisicas
    srand48(entrada.seed);//inica a seed
    initVector(vet, entrada.tam);//inicializa o vetor
    breaks = countBreaks(vet, entrada.tam);//conta as quebras do vetor forncecido
    quickSort3Ins(vet,0,entrada.tam-1,50,&est);//ordena o vator para ter controle sobre o numero de quebras
    std::cout << "size" << " "<< entrada.tam << " " << "seed" << " " << entrada.seed << " "<< "breaks" << " " << breaks <<  std::endl;
    
    simuladorOrdenador(vet,  entrada.tam, entrada.limiarCusto,  entrada.a, entrada.b,  entrada.c,entrada.seed, breaks, &est);//simulador que ira executar 
    free(vet);
  exit(0);
}



