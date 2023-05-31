#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int n = 0;

    printf("Valoarea n în zona secvențială a programului (înainte de constructorul paralel): %d\n", n);

    #pragma omp parallel
    {
        #pragma omp sections lastprivate(n)
        {
            sleep(omp_get_thread_num());

            #pragma omp section
            {
                printf("Valoarea n pentru firul %d (în #pragma omp section - până la inițializare): %d\n", omp_get_thread_num(), n);
                n = 1;
                printf("Valoarea n pentru firul %d (în #pragma omp section - după inițializare): %d\n", omp_get_thread_num(), n);
            }

            #pragma omp section
            {
                printf("Valoarea n pentru firul %d (în #pragma omp section - până la inițializare): %d\n", omp_get_thread_num(), n);
                n = 2;
                printf("Valoarea n pentru firul %d (în #pragma omp section - după inițializare): %d\n", omp_get_thread_num(), n);
            }

            #pragma omp section
            {
                printf("Valoarea n pentru firul %d (în #pragma omp section - până la inițializare): %d\n", omp_get_thread_num(), n);
                n = 3;
                printf("Valoarea n pentru firul %d (în #pragma omp section - după inițializare): %d\n", omp_get_thread_num(), n);
            }
        }

        sleep(omp_get_thread_num());

        printf("Valoarea n pentru firul %d: %d (după #pragma omp section)\n", omp_get_thread_num(), n);
    }

    printf("Valoarea n în zona secvențială a programului (după constructorul paralel): %d\n", n);

    return 0;
}
