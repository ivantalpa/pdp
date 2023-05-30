#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int num = rank * 10; // Each process has a unique number

    int* gathered_data = NULL;
    if (rank == 0) {
        gathered_data = new int[size];
    }

    MPI_Gather(&num, 1, MPI_INT, gathered_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Gathered data: ");
        for (int i = 0; i < size; ++i) {
            printf("%d ", gathered_data[i]);
        }
        printf("\n");
        delete[] gathered_data;
    }

    MPI_Finalize();
}