#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <ctime>

int main(int argc, char *argv[]) {
    int i, k, p, size, rank;
    int rank_gr;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;
    MPI_Group MPI_GROUP_WORLD, newgr;
    MPI_Comm new_comm;
    int* ranks;
    int namelen;
    int dims[1], periods[1], reorder;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);

    if (rank == 0)
        printf("\n=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);

    MPI_Barrier(MPI_COMM_WORLD);

    k = size / 2;  // Assumes size is even
    ranks = (int*)malloc(k * sizeof(int));

    // Select even ranks
    for (i = 0; i < size; i++) {
        if (i % 2 == 0) {
            ranks[i / 2] = i;
        }
    }

    if (rank == 0) {
        printf("Au fost extrase %d numere pare dupa cum urmeaza:\n", k);
        for (i = 0; i < k; i++)
            printf(" %d ", ranks[i]);
        printf(" \n");

        MPI_Barrier(MPI_COMM_WORLD);
    } else {
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Comm_group(MPI_COMM_WORLD, &MPI_GROUP_WORLD);
    MPI_Group_incl(MPI_GROUP_WORLD, k, ranks, &newgr);
    MPI_Comm_create(MPI_COMM_WORLD, newgr, &new_comm);
    MPI_Group_rank(newgr, &rank_gr);

    if (new_comm != MPI_COMM_NULL) {
        dims[0] = k;
        periods[0] = 1;
        reorder = 1;
        MPI_Cart_create(new_comm, 1, dims, periods, reorder, &new_comm);

        int next_rank, previous_rank, rank_send;
        MPI_Cart_shift(new_comm, 0, 1, &previous_rank, &next_rank);

        MPI_Sendrecv(&rank_gr, 1, MPI_INT, next_rank, 0, &rank_send, 1, MPI_INT, previous_rank, 0, new_comm, &status);
        printf("Sunt procesul cu rankul %d (%d) de pe nodul %s. Am primit rankul %d. \n", rank_gr, rank, processor_name, rank_send);
    }

    MPI_Group_free(&newgr);
    MPI_Finalize();
    return 0;
}
