#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <unistd.h>

#define N 1000

int main() {
    int i, iam;
    float a[N], b[N], c[N];

    /* Some initializations */
    for (i = 0; i < N; i++) {
        a[i] = b[i] = i * 1.0;
    }

    #pragma omp parallel shared(a, b, c) private(i, iam)
    {
        #pragma omp sections nowait
        {
            sleep(omp_get_thread_num());

            #pragma omp section
            {
                iam = omp_get_thread_num();
                for (i = 0; i < N / 2; i++) {
                    c[i] = a[i] + b[i];
                }
                printf("Procesul OpenMP cu numarul %d, a determinat %d elemente ale vectorului \n", iam, N / 2);
            }

            #pragma omp section
            {
                iam = omp_get_thread_num();
                for (i = N / 2; i < N; i++) {
                    c[i] = a[i] + b[i];
                }
                printf("Procesul OpenMP cu numarul %d, a determinat %d elemente ale vectorului \n", iam, N / 2);
            }
        }
    }

    return 0;
}
