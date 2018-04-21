#include <stdlib.h>
#include <omp.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

struct matrix {
    int *elements;
    int width;
    int height;
};

struct values {
    double min;
    double max;
    double avg;
    double p25;
    double p50;
    double p75;
};

struct threadArgs {
    struct matrix *a;
    struct matrix *b;
    struct matrix *result;
    int row;
    int count;
};

#define MAX_ELEMENT 10000;

void fill(struct matrix * m);
void fillZero(struct matrix * m);
void * worker(void *vArgs);
void fill(struct matrix * m)
{
    m->elements = (int*) malloc (sizeof(int) * m->width * m->height);

    for (int i = 0; i < m->width; i++) {
        for (int j = 0; j < m->height; j++) {
            m->elements[i * m->width + j] = rand() % MAX_ELEMENT;
        }
    }
}

void fillZero(struct matrix *m)
{
    for (int i = 0; i < m->width; i++) {
        for (int j = 0; j < m->height; j++) {
            m->elements[i * m->width + j] = 0;
        }
    }
}

struct matrix * linemultiply(struct matrix *a, struct matrix *b)
{
    struct matrix *result = (struct matrix *) malloc (sizeof(struct matrix));
    result->width = a->width;
    result->height = b->height;
    result->elements = (int*) malloc (sizeof(int) * a->width * b->height);

    for (int i = 0; i < a->width; i++) {
        for (int j = 0; j < b->height; j++) {
            result->elements[i * result->width + j] = 0;
            for (int k = 0; k < a->width; k++) {
                result->elements[i * a->width + j] += a->elements[i * a->width + k] * b->elements[k * b->width + j];
            }
        }
    }
    return result;
}

struct matrix * mpMltiply(struct matrix *a, struct matrix *b)
{
    struct matrix *result = (struct matrix *) malloc (sizeof(struct matrix));
    int i, j, k;
    result->width = a->width;
    result->height = b->height;
    result->elements = (int*) malloc (sizeof(int) * a->width * b->height);

    #pragma omp parallel for schedule(static,50) collapse(2) private(i,j,k)shared(a,b,result)
    for (i = 0; i < a->width; i++) {
        for (j = 0; j < b->height; j++) {
            result->elements[i * result->width + j] = 0;
            for (k = 0; k < a->width; k++) {
                result->elements[i * a->width + j] += a->elements[i * a->width + k] * b->elements[k * b->width + j];
            }
        }
    }
    return result;
}

struct matrix * dynMpMltiply(struct matrix *a, struct matrix *b)
{
    struct matrix *result = (struct matrix *) malloc (sizeof(struct matrix));
    int i, j, k;
    result->width = a->width;
    result->height = b->height;
    result->elements = (int*) malloc (sizeof(int) * a->width * b->height);

    #pragma omp parallel for schedule(dynamic,50) collapse(2) private(i,j,k) shared(a,b,result)
    for (i = 0; i < a->width; i++) {
        for (j = 0; j < b->height; j++) {
            result->elements[i * result->width + j] = 0;
            for (k = 0; k < a->width; k++) {
                result->elements[i * a->width + j] += a->elements[i * a->width + k] * b->elements[k * b->width + j];
            }
        }
    }
    return result;
}

struct matrix * threadMultiply(struct matrix *a, struct matrix *b, int threadsNum)
{
    struct matrix *result = (struct matrix *) malloc (sizeof(struct matrix));
    int i, j, k;
    int threads;
    result->width = a->width;
    result->height = b->height;
    result->elements = (int*) malloc (sizeof(int) * a->width * b->height);

    struct threadArgs ** args = (struct threadArgs **) malloc(sizeof(struct threadArgs) * threadsNum);

    pthread_t * p = (pthread_t*) malloc (sizeof(pthread_t) * threadsNum);

    for (int j = 0; j < threadsNum; j++) {
        args[j] = new struct threadArgs;
        args[j]->a = a;
        args[j]->b = b;
        args[j]->result = result;
        args[j]->row = j * threadsNum;
        args[j]->count = threadsNum;
        void **arg = (void **)malloc(sizeof(void *));
        arg[0] = args[j];
        pthread_create(&p[j], NULL, worker, args[j]);
    }

    for (int j = 0; j < threadsNum; j++) {
        pthread_join(p[j], NULL);
    }


    return result;
}

void  * worker(void *vArgs)
{
    struct threadArgs *args = (struct threadArgs * )vArgs;
    int * a = args->a->elements;
    int * b = args->b->elements;
    int * result = args->result->elements;
    // printf("id in thread = %d\n", args->id);

    for(int i = args->row; i < args->row + args->count; i++)
        for(int j = 0; j < args->a->width; j++) {
            for(int k = 0; k < args->b->height; k++)
                result[i * args->result->width + j] += a[i * args->a->width + k] * b[k * args->b->width + j];
        }
}

struct values * getValues(std::vector<double> timers)
{
    struct values * result = (struct values*) malloc(sizeof(struct values));
    std::sort(timers.begin(), timers.end());
    result->min = timers[0];
    result->max = timers[timers.size() - 1];
    result->avg = 0;
    result->p25 = timers[timers.size() / 4];
    result->p50 = timers[timers.size() / 2];
    result->p75 = timers[timers.size() * 3 / 4];

    for (size_t i = 0; i < timers.size(); i++) {
        result->avg += timers[i];
    }

    result->avg /= timers.size();

    return result;
}


int main(int argc, char *argv[])
{
    if (argc < 4) return 1;
    int threadsNum = atoi(argv[1]);
    int size = atoi(argv[2]);
    int count = atoi(argv[3]);
    std::vector<double> measurements;

    struct timeval timerBegin, timerEnd;
    struct matrix * a = (struct matrix *) malloc(sizeof(struct matrix));
    a->width = size;
    a->height = size;
    fill(a);

    struct matrix * b = (struct matrix *) malloc(sizeof(struct matrix));
    b->width = size;
    b->height = size;
    fill(b);

    for (int i = 0; i < count; i++) {
        gettimeofday(&timerBegin, NULL);
        linemultiply(a, b);
        gettimeofday(&timerEnd, NULL);
        measurements.push_back((timerEnd.tv_sec-timerBegin.tv_sec) * 1.0f + (timerEnd.tv_usec - timerBegin.tv_usec) / 1000000.0f);
    }

    omp_set_num_threads(threadsNum);
    struct values * timers = getValues(measurements);
    printf("%d;%d;%d;line;%lf;%lf;%lf\n", threadsNum, size, size*size, timers->min, timers->max, timers->avg );;

    for (int i = 0; i < count; i++) {
        gettimeofday(&timerBegin, NULL);
        mpMltiply(a, b);
        gettimeofday(&timerEnd, NULL);
        measurements.push_back((timerEnd.tv_sec-timerBegin.tv_sec) * 1.0f + (timerEnd.tv_usec - timerBegin.tv_usec) / 1000000.0f);
    }

    timers = getValues(measurements);
    printf("%d;%d;%d;statomp;%lf;%lf;%lf\n", threadsNum, size, size*size, timers->min, timers->max, timers->avg );;

    for (int i = 0; i < count; i++) {
        gettimeofday(&timerBegin, NULL);
        dynMpMltiply(a, b);
        gettimeofday(&timerEnd, NULL);
        measurements.push_back((timerEnd.tv_sec-timerBegin.tv_sec) * 1.0f + (timerEnd.tv_usec - timerBegin.tv_usec) / 1000000.0f);
    }

    timers = getValues(measurements);
    printf("%d;%d;%d;dynomp;%lf;%lf;%lf\n", threadsNum, size, size*size, timers->min, timers->max, timers->avg );;

    for (int i = 0; i < count; i++) {

        gettimeofday(&timerBegin, NULL);
        threadMultiply(a, b, threadsNum);
        //dynMpMltiply(a, b);
        gettimeofday(&timerEnd, NULL);
        measurements.push_back((timerEnd.tv_sec-timerBegin.tv_sec) * 1.0f + (timerEnd.tv_usec - timerBegin.tv_usec) / 1000000.0f);
    }

    timers = getValues(measurements);
    printf("%d;%d;%d;threads;%lf;%lf;%lf\n", threadsNum, size, size*size, timers->min, timers->max, timers->avg );;
//    printf("pthreads min = %2f max = %2f avg = %2f\n", threadsTimers->min, threadsTimers->max, threadsTimers->avg );;


    return 0;
}
