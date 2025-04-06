#include "../include/evalenum.hpp"

alg_t algvet[] = {
    {ALGINSERTION, "i"},
    {ALGSELECTION, "s"},
    {ALGQSORT, "q"},
    {ALGQSORT3, "q3"},
    {ALGQSORTINS, "qi"},
    {ALGQSORT3INS, "q3i"},
    {ALGSHELLSORT, "h"},
    {ALGRECSEL, "rs"},
    {0, 0}
};

int name2num(char *name) {
    int i = 0;
    while (algvet[i].num) {
        if (!strcmp(algvet[i].name, name)) return algvet[i].num;
        i++;
    }
    return 0;
}

char *num2name(int num) {
    int i = 0;
    while (algvet[i].num) {
        if (algvet[i].num == num) return algvet[i].name;
        i++;
    }
    return 0;
}

void resetcounter(sortperf_t *s) {
    s->cmp = 0;
    s->move = 0;
    s->calls = 0;
}

void inccmp(sortperf_t *s, int num) {
    s->cmp += num;
}

void incmove(sortperf_t *s, int num) {
    s->move += num;
}

void inccalls(sortperf_t *s, int num) {
    s->calls += num;
}

char *printsortperf(sortperf_t *s, char *str, char *pref) {
    sprintf(str, "%s cmp %d move %d calls %d", pref, s->cmp, s->move, s->calls);
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

void swap(int *xp, int *yp, sortperf_t *s) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
    incmove(s, 3);
}


// shellsort
void shellSort(int *A, int n, sortperf_t * s) {
    if (s) {
        s->cmp = 0;
        s->move = 0;
    }

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = A[i];
            int j;

            for (j = i; j >= gap && A[j - gap] > temp; j -= gap) {
                A[j] = A[j - gap];
                if (s) s->cmp++;
            }

            A[j] = temp;
            if (s && j != i) s->move++;
        }
    }

}


// recursive selection sort
void recursiveSelectionSort(int arr[], int l, int r, sortperf_t * s)
{
    // find the minimum element in the unsorted subarray `[i…n-1]`
    // and swap it with `arr[i]`
    int min = l;
    inccalls(s,1);
    for (int j = l + 1; j <= r; j++)
    {
        // if `arr[j]` is less, then it is the new minimum
	inccmp(s,1);
        if (arr[j] < arr[min]) {
            min = j;    // update the index of minimum element
        }
    }

    // swap the minimum element in subarray `arr[i…n-1]` with `arr[i]`
    if (min!=l)
      swap(&arr[min], &arr[l], s);

    if (l + 1 < r) {
        recursiveSelectionSort(arr, l + 1, r, s);
    }
}

// selection sort
void selectionSort(int arr[], int l, int r, sortperf_t * s) {
    int i, j, min_idx;
    
    // Loop externo sobre todas as posições do array de l até r-1
    for (i = l; i < r; i++) {
        // Assume que o elemento atual é o mínimo
        min_idx = i;
        
        // Encontra o índice do elemento mínimo no subarray não ordenado
        for (j = i + 1; j <= r; j++) {
            // Incrementa contador de comparações
            inccmp(s, 1);
            // Se o elemento em j for menor que o elemento em min_idx, atualiza min_idx
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        // Se o menor elemento não for o elemento atual, troca-os
        if (min_idx != i) {
            swap(&arr[min_idx], &arr[i], s);
        }
    }
    return;
}


//insertion sort
void insertionSort(int v[], int l, int r, sortperf_t * s) {
    int i, j, key;
    
    for (i = l + 1; i <= r; i++) {
        key = v[i];
        j = i - 1;
        
        // Compare key with each element on the left until a smaller element is found
        // or we reach the left boundary
        while (j >= l && v[j] > key) {
            s->cmp++; // Count comparison
            v[j + 1] = v[j]; // Move element one position to the right
            s->move++; // Count movement
            j--;
        }
        
        // If j >= l, we need one more comparison that resulted in exiting the loop
        if (j >= l) s->cmp++;
        
        // Place the key in its correct position
        v[j + 1] = key;
        s->move++; // Count movement for placing key
    }
    
    return;
}

// median of 3 integers
int median (int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
}

void partition3(int *A, int l, int r, int *i, int *j, sortperf_t *s) {
    // Handle base case
    if (r <= l) {
        *i = l;
        *j = r;
        return;
    }
    
    // Find median of three and use it as pivot
    int mid = l + (r - l) / 2;
    int pivot_idx = median(mid, l, r);
    int pivot = A[pivot_idx];
    
    // Move pivot to the beginning
    swap(&A[l], &A[pivot_idx], s);
    
    
    // Initialize pointers for three-way partition
    int lt = l;      // Less than pivot (left boundary)
    int gt = r;      // Greater than pivot (right boundary)
    int i_ptr = l+1; // Current element being examined
    
    // Partition the array
    while (i_ptr <= gt) {
        // Compare current element with pivot
        s->cmp++;
        
        if (A[i_ptr] < pivot) {
            // Element is less than pivot
            swap(&A[lt], &A[i_ptr], s);
            lt++;
            i_ptr++;
        } else if (A[i_ptr] > pivot) {
            // Element is greater than pivot
            swap(&A[i_ptr], &A[gt], s);
            gt--;
        } else {
            // Element is equal to pivot
            i_ptr++;
        }
    }
    // Update output parameters to mark partitioning boundaries
    *i = lt;   // Left boundary (first element == pivot)
    *j = gt;   // Right boundary (last element == pivot)
}



// standard quicksort partition
void partition(int * A, int l, int r, int *i, int *j, sortperf_t *s) {
    int pivot, aux;
    *i = l;
    *j = r;
    
    // Choose the pivot as the middle element
    pivot = A[(*i + *j)/2];
    
    do {
        // Find element on left side that is greater than pivot
        while (A[*i] < pivot) {
            (*i)++;
            s->cmp++;
        }
        
        // Find element on right side that is less than pivot
        while (A[*j] > pivot) {
            (*j)--;
            s->cmp++;
        }
        
        // If we found a pair of elements to swap
        if (*i <= *j) {
            // Swap elements
            swap(&A[*i], &A[*j], s);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

// Implementação do QuickSort padrão
void quickSort(int *A, int l, int r, sortperf_t *s) {
    if (l < r) {
        int i, j;
        
        // Particiona o array e obtém os índices i e j
        partition(A, l, r, &i, &j, s);
        
        // Ordena recursivamente as subpartes
        // Parte esquerda (elementos menores que o pivô)
        quickSort(A, l, j, s);
        
        // Parte direita (elementos maiores que o pivô)
        quickSort(A, i, r, s);
    }
}

// quicksort with median of 3
void quickSort3(int * A, int l, int r, sortperf_t *s) { 
    if (l < r) {
        int i, j;
        
        // Particiona o array e obtém os índices i e j
        partition3(A, l, r, &i, &j, s);
        
        // Ordena recursivamente as subpartes
        // Parte esquerda (elementos menores que o pivô)
        quickSort(A, l, j, s);
        
        // Parte direita (elementos maiores que o pivô)
        quickSort(A, i, r, s);
    }
}

// Quicksort with insertion sort for small partitions
void quickSortIns(int * A, int l, int r, sortperf_t *s) {
    // Define threshold for small partitions
    const int THRESHOLD = 10;
    
    // Base case: if the partition is smaller than threshold or invalid
    if (l >= r) {
        return;
    }
    
    // For small partitions, use insertion sort
    if (r - l + 1 <= THRESHOLD) {
        insertionSort(A, l, r, s);
        return;
    }
    
    // For larger partitions, use partition3 and then recurse
    int i, j;
    
    // Partition the array
    partition(A, l, r, &i, &j, s);
    
    // Recursively sort the partitions
    quickSortIns(A, l, j, s);
}
// quicksort with insertion for small partitions and median of 3
void quickSort3Ins(int * A, int l, int r, sortperf_t *s) { 
    // Define threshold for small partitions
    const int THRESHOLD = 10;
    
    // Base case: if the partition is smaller than threshold or invalid
    if (l >= r) {
        return;
    }
    
    // For small partitions, use insertion sort
    if (r - l + 1 <= THRESHOLD) {
        insertionSort(A, l, r, s);
        return;
    }
    
    // For larger partitions, use partition3 and then recurse
    int i, j;
    
    // Partition the array
    partition3(A, l, r, &i, &j, s);
    
    // Recursively sort the partitions
    quickSortIns(A, l, j, s);
}
void uso() {
    fprintf(stderr, "sortperf\n");
    fprintf(stderr, "\t-z <int>\t(vector size)\n");
    fprintf(stderr, "\t-s <int>\t(initialization seed)\n");
    fprintf(stderr, "\t-a <s|i|q|q3|qi|q3i|h|rs>\t(algorithm)\n");
    fprintf(stderr, "\t    s\tselection\n");
    fprintf(stderr, "\t    i\tinsertion\n");
    fprintf(stderr, "\t    q\tquicksort\n");
    fprintf(stderr, "\t    q3\tquicksort+median3\n");
    fprintf(stderr, "\t    qi\tquicksort+insertion\n");
    fprintf(stderr, "\t    q3i\tquicksort+median3+insertion\n");
    fprintf(stderr, "\t    h\theapsort\n");
    fprintf(stderr, "\t    rs\trecursive selection\n");
}

void parse_args(int argc, char **argv, opt_t *opt) {
    extern char *optarg;
    extern int optind;
    int c;
    opt->seed = 1;
    opt->size = 10;
    opt->alg = 1;

    while ((c = getopt(argc, argv, "z:s:a:h")) != EOF) {
        switch (c) {
            case 'z':
                opt->size = atoi(optarg);
                break;
            case 's':
                opt->seed = atoi(optarg);
                break;
            case 'a':
                opt->alg = name2num(optarg);
                break;
            case 'h':
            default:
                uso();
                exit(1);
        }
    }
    if (!opt->alg) {
        uso();
        exit(1);
    }
}

void clkDiff(struct timespec t1, struct timespec t2, struct timespec *res) {
    if (t2.tv_nsec < t1.tv_nsec) {
        res->tv_nsec = 1000000000 + t2.tv_nsec - t1.tv_nsec;
        res->tv_sec = t2.tv_sec - t1.tv_sec - 1;
    } else {
        res->tv_nsec = t2.tv_nsec - t1.tv_nsec;
        res->tv_sec = t2.tv_sec - t1.tv_sec;
    }
}


