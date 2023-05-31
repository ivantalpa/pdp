#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int numtask, sendcount, reccount, source;
    double *A;
    int i, myrank, root = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtask);

    int rows = 10; // Example of arbitrary rows
    int cols = numtask; // Still keeping number of cols as numtask for simplicity
    double ain[rows], aout[cols];
    int ind[cols];

    struct {
        double val;
        int rank;
    } în[rows], out[cols];

    sendcount = rows;
    reccount = rows;

    if (myrank == root) {
        printf("===== Rezultatele programului '%s' =====\n", argv[0]);
        A = (double*)malloc(rows * cols * sizeof(double));

        for (int i = 0; i < rows * cols; i++)
            A[i] = rand() / 1000000000.0;

        printf("Tipar datele initiale\n");

        for (int i = 0; i < rows; i++) {
            printf("\n");

            for (int j = 0; j < cols; j++) {
                printf("A[%d,%d]=%.2f ", i, j, A[i * cols + j]);
            }
        }

        printf("\n");
        MPI_Barrier(MPI_COMM_WORLD);
    } else {
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Scatter(A, sendcount, MPI_DOUBLE, ain, reccount, MPI_DOUBLE, root, MPI_COMM_WORLD);

    for (i = 0; i < rows; ++i) {
        în[i].val = ain[i];
        în[i].rank = myrank;
    }

    MPI_Reduce(în, out, rows, MPI_DOUBLE_INT, MPI_MAXLOC, root, MPI_COMM_WORLD);

    if (myrank == root) {
        printf("\n");
        printf("Valorile maximale de pe coloane și indicele liniei:\n");

        for (i = 0; i < cols; ++i) {
            aout[i] = out[i].val;
            ind[i] = out[i].rank;
            printf("Coloana %d, valoarea=%.2f, linia=%d\n", i, aout[i], ind[i]);
        }
    }

    free(A);
    MPI_Finalize();
    return 0;
}
