#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void hTest(int N, int *a, int *b)
{
    for (int i = 0; i < N; i++)
        a[i] += b[i];
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "USAGE: lab2 <N> <threads>\n");
        return -1;
    }
    
    int num_threads = atoi(argv[2]);
    omp_set_num_threads(num_threads);

    double timer, timer_alloc;
    clock_t start, start_alloc, stop;
    
    int N = 1 << atoi(argv[1]);
    if (N == 1)
        N = 1 << 30;

    start_alloc = clock();
    int *a = (int *)calloc(N, sizeof(int));
    int *b = (int *)calloc(N, sizeof(int));

    for (int i = 0; i < N; i++)
    {
        a[i] = 2 * i;
        b[i] = 2 * i + 1;
    }
    int i;
    start = clock();
#pragma omp parallel for shared(a, b) private(i) schedule(static, num_threads)
    for (i = 0; i < N; i++)
    {
        a[i] += b[i];
        // Which thread am I? Show who works on what for this samll example
        printf("Thread %d works on element%d\n", omp_get_thread_num(), i);
    }
    stop = clock();
    timer = 1000 * ((double)(stop - start)) / (double)CLOCKS_PER_SEC;
    timer_alloc = 1000 * ((double)(stop - start_alloc)) / (double)CLOCKS_PER_SEC;

    for (int i = 0; i < N; i += N / 16)
        fprintf(stdout, "%d\t%d\t%d\n", i, a[i], b[i]);
    fprintf(stderr, "Elapsed time: %g ms (%g ms)з\n", timer, timer_alloc);
    return 0;
}
