#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <unistd.h>

int n;

#pragma omp threadprivate(n)

int main(int argc, char *argv[]) {
    n = 1;

    #pragma omp parallel copyin(n)
    {
        sleep(omp_get_thread_num());
        printf("Valoarea n în prima regiune paralela a firului %d: %d\n", omp_get_thread_num(), n);
    }

    printf("************************************\n");
    printf("Aici firul Master execută un cod serial\n");
    printf("************************************\n");

    n = 2;

    #pragma omp parallel copyin(n)
    {
        sleep(omp_get_thread_num());
        printf("Valoarea n în a doua regiune paralela a firului %d: %d\n", omp_get_thread_num(), n);
    }

    printf("************************************\n");
    printf("Aici firul Master execută un cod serial\n");
    printf("************************************\n");

    #pragma omp parallel
    {
        sleep(omp_get_thread_num());
        printf("Valoarea n în a treia regiune paralela a firului %d: %d\n", omp_get_thread_num(), n);
    }

    return 0;
}