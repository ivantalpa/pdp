#include <stdio.h>
#include <omp.h>
#include <iostream>

int main(int argc, char *argv[]) {
    int n = 1;

    printf("Valoarea lui n pana la directiva parallel cu clauza firstprivate: %d\n", n);

    #pragma omp parallel firstprivate(n)
    {
        sleep(omp_get_thread_num());
        printf("OpenMP procesul %d - valoarea lui n dupa clauza firstprivate: %d\n", omp_get_thread_num(), n);
        n = omp_get_thread_num();
        printf("OpenMP procesul %d - valoarea lui n dupa initializare de catre fire: %d\n", omp_get_thread_num(), n);
    }

    printf("Valoarea lui n dupa directiva parallel cu clauza firstprivate: %d\n", n);

    return 0;
}
