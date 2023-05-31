#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    printf("Valoarea initiala (prestabilita) a variabilei de mediu OMP_DYNAMIC: %d\n", omp_get_dynamic());
    omp_set_dynamic(0);
    printf("Valoarea variabilei de mediu dupa executarea rutinei omp_set_dynamic() OMP_DYNAMIC: %d\n", omp_get_dynamic());

    #pragma omp parallel num_threads(128)
    {
        #pragma omp master
        {
            printf("Regiunea paralela contine %d fire\n", omp_get_num_threads());
        }
    }
}
