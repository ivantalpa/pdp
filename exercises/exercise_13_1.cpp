#include <omp.h>
#include <stdio.h>
#include <unistd.h>

#define CHUNKSIZE 100
#define N 1000

int main() {
    int i, k, chunk, iam;
    float a[N], b[N], c[N];

    /* initializare vectorilor */
    for (i = 0; i < N; i++) {
        a[i] = b[i] = i * 1.0;
    }

    chunk = CHUNKSIZE;

    #pragma omp parallel shared(a, b, c, chunk) private(i, k, iam)
    {
        k = 0;
        iam = omp_get_thread_num();

        #pragma omp for schedule(static, chunk) nowait
        for (i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
            k = k + 1;
        }

        sleep(iam);

        printf("Procesul OpenMP cu numarul %d, a determinat %d elemente ale vectorului \n", iam, k);
    }

    return 0;
}
