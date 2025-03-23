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
  return;
}

//insertion sort
void insertionSort(int v[], int l, int r, sortperf_t * s) {
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

// quicksort partition using median of 3
void partition3(int * A, int l, int r, int *i, int *j, sortperf_t *s) {
}

// standard quicksort partition
void partition(int * A, int l, int r, int *i, int *j, sortperf_t *s) {
}

// standard quicksort
void quickSort(int * A, int l, int r, sortperf_t *s) { 
}

// quicksort with median of 3
void quickSort3(int * A, int l, int r, sortperf_t *s) { 
}

// quicksort with insertion for small partitions
void quickSortIns(int * A, int l, int r, sortperf_t *s) { 
}

// quicksort with insertion for small partitions and median of 3
void quickSort3Ins(int * A, int l, int r, sortperf_t *s) { 
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


