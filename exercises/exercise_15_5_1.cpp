#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifdef _OPENMP
#include <omp.h>
#define TRUE 1
#define FALSE 0
#else
#define omp_get_thread_num() 0
#define omp_get_num_threads() 1
#define omp_get_nested() 0
#endif

int main() {
    int id;

#ifdef _OPENMP
    (void) omp_set_dynamic(FALSE);
    if (omp_get_dynamic()) {
        printf("Warning: dynamic adjustment of threads has been set\n");
    }
    (void) omp_set_num_threads(3);
    (void) omp_set_nested(1);
    if (!omp_get_nested()) {
        printf("Warning: nested parallelism not set\n");
    }
#endif

    printf("Nested parallelism is %s\n", omp_get_nested() ? "supported" : "not supported");

    #pragma omp parallel private(id)
    {
        id = omp_get_thread_num();

        #pragma omp parallel num_threads(2)
        {
            sleep(id);
            printf(" Thread %d from outer parallel region executes the thread %d from inner parallel region\n", id, omp_get_thread_num());
        }
        // End of inner parallel region
    }
    // End of outer parallel region

    return 0;
}
