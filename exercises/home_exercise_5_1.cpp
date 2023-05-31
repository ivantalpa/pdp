#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("=====REZULTATUL PROGRAMULUI '%s'\n", argv[0]);
    }

    int sendValue = rank + 1;
    int recvValue;

    MPI_Allreduce(&sendValue, &recvValue, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("Procesul %d: sendValue = %d, recvValue = %d\n", rank, sendValue, recvValue);

    MPI_Finalize();

    return 0;
}
