#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

struct Pair {
    double val;
    int rank;
};

void maxloc(void *in, void *inout, int *len, MPI_Datatype *dptr) {
    Pair *inpair = (Pair*) in;
    Pair *inoutpair = (Pair*) inout;

    for (int i = 0; i < *len; ++i) {
        if (inoutpair[i].val < inpair[i].val) {
            inoutpair[i].val = inpair[i].val;
            inoutpair[i].rank = inpair[i].rank;
        } else if (inoutpair[i].val == inpair[i].val) {
            if (inoutpair[i].rank > inpair[i].rank) {
                inoutpair[i].rank = inpair[i].rank;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int numtask, myrank, root = 0;
    double *A;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtask);

    Pair în[numtask], out[numtask];
    MPI_Op MPI_ALLMAXLOC;
    MPI_Datatype MPI_PAIR;

    MPI_Type_contiguous(2, MPI_DOUBLE, &MPI_PAIR);
    MPI_Type_commit(&MPI_PAIR);

    MPI_Op_create(maxloc, 1, &MPI_ALLMAXLOC);

    if (myrank == root) {
        printf("===== Rezultatele programului '%s' =====\n", argv[0]);
        A = (double*)malloc(numtask * numtask * sizeof(double));

        for (int i = 0; i < numtask * numtask; i++)
            A[i] = rand() / 1000000000.0;

        printf("Tipar datele initiale\n");

        for (int i = 0; i < numtask; i++) {
            printf("\n");

            for (int j = 0; j < numtask; j++) {
                printf("A[%d,%d]=%.2f ", i, j, A[i * numtask + j]);
            }
        }

        printf("\n");
        MPI_Barrier(MPI_COMM_WORLD);
    } else {
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Scatter(A, numtask, MPI_DOUBLE, în, numtask, MPI_DOUBLE, root, MPI_COMM_WORLD);

    for (int i = 0; i < numtask; ++i) {
        în[i].val = A[i];
        în[i].rank = myrank;
    }

    MPI_Allreduce(în, out, numtask, MPI_PAIR, MPI_ALLMAXLOC, MPI_COMM_WORLD);

    if (myrank == root) {
        printf("\n");
        printf("Valorile maximale de pe coloane și indicele liniei:\n");

        for (int i = 0; i < numtask; ++i) {
            printf("Coloana %d, valoarea=%.2f, linia=%d\n", i, out[i].val, out[i].rank);
        }
    }

    MPI_Op_free(&MPI_ALLMAXLOC);
    MPI_Type_free(&MPI_PAIR);
    MPI_Finalize();

    if (myrank == root) {
        free(A);
    }

    return 0;
}
