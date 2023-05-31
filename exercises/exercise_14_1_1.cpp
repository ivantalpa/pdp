#include <stdio.h>
#include <omp.h>
#include <iostream>

int main(int argc, char *argv[]) {
    int n = 1, iam;

    printf("Valoarea lui n pana la directiva parallel cu clauza private: %d\n", n);

    #pragma omp parallel private(n, iam)
    {
        sleep(omp_get_thread_num());
        printf("OpenMP procesul %d - valoarea lui n dupa clauza private: %d\n", omp_get_thread_num(), n);
        n = omp_get_thread_num();
        printf("OpenMP procesul %d - valoarea lui n dupa initializare de catre fir: %d\n", omp_get_thread_num(), n);
    }

    printf("Valoarea lui n dupa directiva parallel cu clauza private: %d\n", n);

    return 0;
}
