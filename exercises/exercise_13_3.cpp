#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int x, i;
    x = 0;
    omp_set_num_threads(2);

    #pragma omp parallel shared(x) private(i)
    {
        for (i = 0; i < 1000; i++) {
            #pragma omp critical
            {
                x = x + 1;
            }
        }
    }

    printf("Valoarea lui x=%d \n", x);

    return 0;
}
