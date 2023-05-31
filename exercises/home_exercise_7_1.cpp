#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i, p, size, rank;
    int rank_gr;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;
    MPI_Group MPI_GROUP_WORLD, newgr;
    int* ranks;
    int namelen;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);

    if (rank == 0)
        printf("\n=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);

    MPI_Barrier(MPI_COMM_WORLD);

    // calculate the number of ranks that are divisible by 3
    int k = size / 3;
    ranks = (int*)malloc(k * sizeof(int));

    // Populate ranks with the processes whose ranks are divisible by 3
    for (i = 0; i < k; i++) {
        ranks[i] = i * 3;
    }

    if (rank == 0) {
        printf("Au fost extrase %d numere dupa cum urmeaza:\n", k);
        for (i = 0; i < k; i++)
            printf(" %d ", ranks[i]);
        printf(" \n");

        MPI_Barrier(MPI_COMM_WORLD);
    } else {
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Comm_group(MPI_COMM_WORLD, &MPI_GROUP_WORLD);
    MPI_Group_incl(MPI_GROUP_WORLD, k, ranks, &newgr);
    MPI_Group_rank(newgr, &rank_gr);

    if (rank_gr != MPI_UNDEFINED)
        printf("Sunt procesul cu rankul %d (%d) de pe nodul %s. \n", rank_gr, rank, processor_name);

    MPI_Group_free(&newgr);
    MPI_Finalize();
    return 0;
}
