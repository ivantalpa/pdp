#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#ifdef _OPENMP
#include <omp.h>
#define TRUE 1
#define FALSE 0
#else
#define omp_get_thread_num() 0
#endif

double f(double y) {
    return (4.0 / (1.0 + y * y));
}

int main() {
    double w, x, sum, pi, a, b;
    int i, MPIrank;
    int n = 1000000;
    int Nodes = 1;
    MPIrank = 0;

    w = 1.0 / n;
    sum = 0.0;
    a = (MPIrank + 0.0) / Nodes;
    b = (MPIrank + 1.0) / Nodes;

    omp_set_num_threads(2);

    #pragma omp parallel private(x) shared(w, a, b) reduction(+:sum)
    {
        #pragma omp master
        {
            printf("Pentru fiecare proces MPI se genereaza %d procese OpenMP (fire)\n", omp_get_num_threads());
        }

        #pragma omp for nowait
        for (i = 0; i < n; i++) {
            x = a + (b - a) * w * (i - 0.5);
            sum = sum + f(x);
        }

        sleep(omp_get_thread_num());

        printf("Procesul OpenMP cu numarul %d, a determinat integrala egala cu %f\n", omp_get_thread_num(), (b - a) * w * sum);
    }

    pi = (b - a) * w * sum;
    printf("Valoare finala, pi = %f\n", pi);

    return 0;
}
