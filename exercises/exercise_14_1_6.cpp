#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <unistd.h>

int main() {
    int i, n, chunk, k;
    float a[100], b[100], result;

    /* Se initializeaza valorile */
    n = 100;
    chunk = 10;
    result = 0.0;

    for (i = 0; i < n; i++) {
        a[i] = 1;//i * 1.0;
        b[i] = 1;//i * 2.0;
    }

    omp_set_num_threads(2);

    #pragma omp parallel default(shared) private(i, k) reduction(+:result)
    {
        k = 0;

        #pragma omp for schedule(dynamic, chunk) nowait
        for (i = 0; i < n; i++) {
            k = k + 1;
            result = result + (a[i] * b[i]);
        }

        sleep(omp_get_thread_num());

        printf("Procesul OpenMP cu numarul %d, a determinat %d elemente ale produsului scalar egal cu %f\n", omp_get_thread_num(), k, result);
    }

    printf("Produsul scalar este = %f\n", result);

    return 0;
}
