#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <unistd.h>

int a, b, i, tid;
float x;

#pragma omp threadprivate(a, x)

int main() {
    /* Explicitly turn off dynamic threads */
    omp_set_dynamic(0);

    printf("Prima regiune paralela:\n");

    #pragma omp parallel private(b, tid)
    {
        tid = omp_get_thread_num();
        a = tid;
        b = tid;
        x = 1.1 * tid + 1.0;
        sleep(omp_get_thread_num());
        printf("Procesul OpenMP %d: a,b,x= %d %d %f\n", tid, a, b, x);
    } /* end of parallel section */

    printf("************************************\n");
    printf("Aici firul Master executa un cod serial\n");
    printf("************************************\n");
    printf("A doua regiune paralela:\n");

    #pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        sleep(omp_get_thread_num());
        printf("Procesul OpenMP %d: a,b,x= %d %d %f\n", tid, a, b, x);
    } /* end of parallel section */

    return 0;
}
