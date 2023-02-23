#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    fprintf(stderr, "USAGE: lab2 <N>\n");
    return -1;
  }

  double timer, timer_alloc;
  clock_t start_alloc, start, stop;

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

  start = clock();
  for (int i = 0; i < N; i++)
    a[i] += b[i];

  stop = clock();
  timer = 1000 * ((double)(stop - start)) / (double)CLOCKS_PER_SEC;
  timer_alloc = 1000 * ((double)(stop - start_alloc)) / (double)CLOCKS_PER_SEC;

  for (int i = 0; i < N; i += N / 16)
    fprintf(stdout, "%d\t%d\t%d\n", i, a[i], b[i]);

  fprintf(stderr, "Elapsed time: %g ms (alloc: %g ms)\n", timer, timer_alloc);

  return 0;
}
