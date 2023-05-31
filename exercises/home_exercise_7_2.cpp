#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <ctime>

int main(int argc, char *argv[]) {
    int size, rank;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int namelen;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);

    if (rank == 0)
        printf("\n=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);

    MPI_Barrier(MPI_COMM_WORLD);

    // Initialize matrix and populate it with random values.
    int** matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 100;
        }
    }

    // For each column, processes with even rank find the max, processes with odd rank find the min.
    int max = -1, min = 101;  // Assuming elements of the matrix are in [0,100]
    for (int col = 0; col < size; col++) {
        int columnValue = matrix[rank][col];

        if (rank % 2 == 0) {
            // If rank is even, find max
            int localMax;
            MPI_Reduce(&columnValue, &localMax, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
            if (rank == 0 && localMax > max) {
                max = localMax;
            }
        } else {
            // If rank is odd, find min
            int localMin;
            MPI_Reduce(&columnValue, &localMin, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
            if (rank == 1 && localMin < min) {
                min = localMin;
            }
        }
    }

    if (rank == 0) {
        printf("Maximul este: %d\n", max);
    } else if (rank == 1) {
        printf("Minimul este: %d\n", min);
    }

    MPI_Finalize();
    return 0;
}
