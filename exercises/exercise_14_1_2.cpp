#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int i, m[5];

    printf("Vectorul m pana la directiva parallel shared:\n");

    /* Se initializeaza vectorul m */
    for (i = 0; i < 5; i++) {
        m[i] = 0;
        printf("%d\n", m[i]);
    }

    #pragma omp parallel shared(m)
    {
        /* Se atribuie valoarea 1 elementului cu indicele egal cu numarul firului din vectorul m */
        m[omp_get_thread_num()] = 1;
    }

    printf("Valoarea vectorului dupa directiva parallel shared:\n");
    for (i = 0; i < 5; i++) {
        printf("%d\n", m[i]);
    }

    return 0;
}
