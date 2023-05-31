#include <stdio.h>
#include <omp.h>
#include <iostream>

omp_lock_t lock, lock1;

int main(int argc, char *argv[]) {
    int n;

    omp_init_lock(&lock);
    omp_init_lock(&lock1);
    omp_set_num_threads(3);

    #pragma omp parallel private(n)
    {
        omp_set_lock(&lock1);

        #pragma omp master
        {
            printf("Se genereaza %d procese OpenMP (fire)\n", omp_get_num_threads());
        }

        omp_unset_lock(&lock1);

        n = omp_get_thread_num();
        omp_set_lock(&lock);

        printf("=================\n");
        printf("Inceputul sectiei inchise, firul %d\n", n);
        printf("Sfarsitul sectiei inchise, firul %d\n", n);
        printf("=================\n");
        printf("\n");

        omp_unset_lock(&lock);
    }

    omp_destroy_lock(&lock1);
    omp_destroy_lock(&lock);
}
