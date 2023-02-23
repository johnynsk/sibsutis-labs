#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/sort.h>
#include <thrust/copy.h>
#include <thrust/random.h>
#include <thrust/functional.h>

using namespace thrust::placeholders;

struct saxpy_functor
{
    const int a;

    saxpy_functor(int _a) : a(_a) {}

    __host__ __device__ int operator()(const int &b) const
    {
        return a + b;
    }
} functorx;
/*
void fast_fast_fast(int A, thrust::device_vector<int>& B)
{
    // B <- A  + B
    thrust::transform(B.begin(), B.begin(), saxpy_functor(A));
}
*/
/*
template <typename T = void>
struct myplus
{
    typedef T first_argument_type;
    typedef T second_argument_type;
    typedef T result_type;
    __thrust_exec_check_disable__
        __host__ __device__ constexpr T
        operator()(const T &lhs, const T &rhs) const
    {
        return lhs + rhs;
    }
};
*/
int main(int argc, char **argv)
{
    double timer, timer_alloc;
    clock_t start, start_alloc, stop;
    if (argc < 2)
    {
        std::cerr << "You should put second argument as log_2(N)" << std::endl;
        return 1;
    }

    int logN = atoi(argv[1]);
    logN = logN < 4 || logN > 30 ? 4 : logN;
    int N = 1 << logN;

    thrust::host_vector<int> h(1 << logN);
    thrust::generate(h.begin(), h.end(), rand);

    thrust::device_vector<int> a(1 << logN);
    thrust::device_vector<int> b(1 << logN);

    for (int i = 0; i < N; i += N / 16)
    {
        std::cout << h[i] << std::endl;
    }

    start_alloc = clock();

    thrust::copy(h.begin(), h.end(), a.begin());
    thrust::copy(h.begin(), h.end(), b.begin());
    thrust::sort(b.begin(), b.end());

    // for (int i = 0; i < logN; i++) {
    start = clock();
    thrust::transform(a.begin(), a.end(), b.begin(), b.begin(), thrust::plus<int>());
    thrust::transform(a.begin(), a.end(), b.begin(), b.begin(), functorx);
    // }

    stop = clock();
    timer = 1000 * ((double)(stop - start)) / (double)CLOCKS_PER_SEC;
    timer_alloc = 1000 * ((double)(stop - start_alloc)) / (double)CLOCKS_PER_SEC;

    std::cout << std::endl;
    thrust::copy(a.begin(), a.end(), h.begin());

    for (int i = 0; i < N; i += N / 16)
    {
        std::cout << h[i] << std::endl;
    }

    std::cout << "Thrust Elapsed time: " << timer << " ms (" << timer_alloc << " ms)" << std::endl;
}