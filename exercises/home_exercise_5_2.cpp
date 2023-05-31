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

    double number;
    if (rank % 2 == 0) {
        number = rank * 1.5;
    } else {
        number = rank * 2.5;
    }

    double minVal, maxVal;
    MPI_Reduce(&number, &minVal, 1, MPI_DOUBLE, MPI_MIN, 1, MPI_COMM_WORLD);
    MPI_Reduce(&number, &maxVal, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank % 2 == 0) {
        printf("Procesul %d: Element maximal = %.2f\n", rank, maxVal);
    } else {
        printf("Procesul %d: Element minimal = %.2f\n", rank, minVal);
    }

    MPI_Finalize();

    return 0;
}
