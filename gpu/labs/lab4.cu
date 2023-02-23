#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

__global__ void gInit(int *a, int *b)
{
  int i = threadIdx.x + blockIdx.x * blockDim.x;
  a[i] = 2 * i;
  b[i] = 2 * i + 1;
}

__global__ void gSum(int *a, int *b)
{
  int i = threadIdx.x + blockIdx.x * blockDim.x;
  a[i] += b[i];
}

// a[i] := 2*i + (b[i]) := 2*i + 2*i + 1 = 4*i + 1;

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    fprintf(stderr, "USAGE: <prog> <log_2{N}> <num_threads>");
    return -1;
  }

  double timer, timer_alloc;
  clock_t start, start_alloc, stop;
  cudaEvent_t startE, stopE;
  cudaEventCreate(&startE);
  cudaEventCreate(&stopE);
  float gpuTime = 0.0f;

  int N = 1 << atoi(argv[1]);
  if (N == 1)
    N = 30720;
  int num_threads = atoi(argv[2]);
  int num_blocks = N / num_threads;

  int *a, *b;
  int *a_h;

  start_alloc = clock();
  cudaMalloc((void **)&a, N * sizeof(int));
  cudaMalloc((void **)&b, N * sizeof(int));
  a_h = (int *)calloc(N, sizeof(int));

  gInit<<<num_blocks, num_threads>>>(a, b);
  cudaDeviceSynchronize();

  cudaEventRecord(startE, 0);
  start = clock();
  gSum<<<num_blocks, num_threads>>>(a, b);
  cudaDeviceSynchronize();
  cudaEventRecord(stopE, 0);
  cudaEventSynchronize(stopE);
  cudaEventElapsedTime(&gpuTime, startE, stopE);

  cudaMemcpy(a_h, a, N * sizeof(int), cudaMemcpyDeviceToHost);

  stop = clock();
  timer = 1000 * ((double)(stop - start)) / (double)CLOCKS_PER_SEC;
  timer_alloc = 1000 * ((double)(stop - start_alloc)) / (double)CLOCKS_PER_SEC;

  // for (int i = 0; i < N; i += N / 16)
  // fprintf(stdout, "%d\n", a_h[i]);

  fprintf(stdout, "CUDA Elapsed time: %g ms (%g ms)\n", gpuTime, timer_alloc);

  cudaFree(a);
  cudaFree(b);
  free(a_h);

  return 0;
}
