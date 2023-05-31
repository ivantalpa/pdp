#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <ctime>

int main(int argc, char *argv[]) {
    int i, k, p, size, rank;
    int rank_gr;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;
    MPI_Group MPI_GROUP_WORLD, newgr1, newgr2;
    MPI_Comm new_comm1, new_comm2;
    int* ranks1;
    int* ranks2;
    int namelen;
    int dims[1], periods[1], reorder;
    int data;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);

    if (rank == 0)
        printf("\n=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);

    MPI_Barrier(MPI_COMM_WORLD);

    k = size / 2;  // Assumes size is even
    ranks1 = (int*)malloc(k * sizeof(int));
    ranks2 = (int*)malloc(k * sizeof(int));

    // Create two groups with different sets of ranks
    for (i = 0; i < size; i++) {
        if (i < k) {
            ranks1[i] = i;
        } else {
            ranks2[i - k] = i;
        }
    }

    MPI_Comm_group(MPI_COMM_WORLD, &MPI_GROUP_WORLD);
    MPI_Group_incl(MPI_GROUP_WORLD, k, ranks1, &newgr1);
    MPI_Group_incl(MPI_GROUP_WORLD, k, ranks2, &newgr2);

    MPI_Comm_create(MPI_COMM_WORLD, newgr1, &new_comm1);
    MPI_Comm_create(MPI_COMM_WORLD, newgr2, &new_comm2);

    MPI_Group_rank(newgr1, &rank_gr);

    if (new_comm1 != MPI_COMM_NULL) {
        dims[0] = k;
        periods[0] = 1;
        reorder = 1;
        MPI_Cart_create(new_comm1, 1, dims, periods, reorder, &new_comm1);

        int next_rank, previous_rank;
        MPI_Cart_shift(new_comm1, 0, 1, &previous_rank, &next_rank);

        data = rank_gr;
        MPI_Sendrecv_replace(&data, 1, MPI_INT, next_rank, 0, previous_rank, 0, new_comm1, &status);
        printf("Grupul 1 - Sunt procesul cu rankul %d (%d) de pe nodul %s. Am primit datele %d. \n", rank_gr, rank, processor_name, data);
    }

    MPI_Group_rank(newgr2, &rank_gr);

    if (new_comm2 != MPI_COMM_NULL) {
        data = rank_gr;
        if (rank_gr == 0) {  // master
            for (i = 1; i < k; i++) {
                MPI_Send(&data, 1, MPI_INT, i, 0, new_comm2);
            }
        } else {  // slaves
            MPI_Recv(&data, 1, MPI_INT, 0, 0, new_comm2, &status);
            printf("Grupul 2 - Sunt procesul cu rankul %d (%d) de pe nodul %s. Am primit datele %d de la master. \n", rank_gr, rank, processor_name, data);
        }
    }

    MPI_Group_free(&newgr1);
    MPI_Group_free(&newgr2);
    MPI_Finalize();
    return 0;
}