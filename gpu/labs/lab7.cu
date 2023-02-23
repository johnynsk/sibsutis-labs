  #include <thrust/host_vector.h>
  #include <thrust/device_vector.h>
  #include <thrust/generate.h>
  #include <thrust/sort.h>
  #include <thrust/copy.h>
  #include <thrust/random.h>
  #include <iostream>
  #include <time.h>

  int main(int argc, char **argv) {
    double timer, timer_alloc;
    clock_t start, start_alloc, stop;

    cudaEvent_t startE, stopE;
    float gpuTime = 0.0f;

    int N = atoi(argv[1]);

    cudaEventCreate ( &startE );
    cudaEventCreate ( &stopE ); 
    
    
    thrust::host_vector<int> h_vec_0(1 << atoi(argv[1]));
    thrust::device_vector<int> d_vec_1(1 << atoi(argv[1]));
    thrust::device_vector<int> d_vec_2(1 << atoi(argv[1]));
    
    start_alloc = clock();

    thrust::generate(thrust::host, h_vec_0.begin(), h_vec_0.end(), rand);
    thrust::copy(h_vec_0.begin(), h_vec_0.end(), d_vec_1.begin());
    thrust::copy(h_vec_0.begin(), h_vec_0.end(), d_vec_2.begin());
    thrust::sort(d_vec_2.begin(), d_vec_2.end());
    
    start = clock();

    cudaEventRecord ( startE, 0 );
    thrust::transform(d_vec_1.begin(), d_vec_1.end(), d_vec_2.begin(), d_vec_2.begin(), thrust::plus<int>());
    cudaEventRecord ( stopE, 0 );
    cudaEventSynchronize ( stopE );
    cudaEventElapsedTime ( &gpuTime, startE, stopE );
    stop = clock();
    
    timer = 1000 * ((double)(stop - start)) / (double)CLOCKS_PER_SEC;
    timer_alloc = 1000 * ((double)(stop - start_alloc)) / (double)CLOCKS_PER_SEC;

    thrust::copy(d_vec_2.begin(), d_vec_2.end(), h_vec_0.begin());

    for (int i = 0; i < (1 << N); i += (1 << N) / 16)
    {
        std::cout << h_vec_0[i] << std::endl;
    }
    
    fprintf(stdout, "Thrust Elapsed time: %f ms (%g ms)\n", gpuTime, timer_alloc);

    //td::cout << "time: " << gpuTime << "sec" << std::endl;
  }

