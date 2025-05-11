#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include "../include/heap.hpp"
#include <sstream>
#include <string>

int main(){
    int n;
    std::cin >> n;

    Heap heap(n);
    for (int i = 0; i < n; i++) {
        int elemento;
        std::cin >> elemento;
        heap.Inserir(elemento);
    }
   
    while (!heap.Vazio()) {
        std::cout << heap.Remover() << " ";
    }
    std::cout << std::endl;


    return 0;
}