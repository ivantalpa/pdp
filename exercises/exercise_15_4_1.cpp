#include <stdio.h>
#include <omp.h>

void mode(void) {
    if (omp_in_parallel()) {
        printf("Se executa instructiuni din regiunea paralela\n");
    } else {
        printf("Se executa instructiuni din regiunea secventiala\n");
    }
}

int main(int argc, char *argv[]) {
    mode();

    #pragma omp parallel
    {
        #pragma omp master
        {
            mode();
        }
    }
}
