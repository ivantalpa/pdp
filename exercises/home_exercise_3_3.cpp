#include <stdio.h>
#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]) {
    int size, rank, t, namelen;
    int incep = 8; // You might want to modify this depending on your needs
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);

    double start_time, end_time; // For timing

    if (rank == 0)
        printf("\n=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);

    start_time = MPI_Wtime(); // Start the timer

    MPI_Sendrecv(&rank, 1, MPI_INT, (rank + 1) % size, 10,
                 &t, 1, MPI_INT, (rank + size - 1) % size, 10,
                 MPI_COMM_WORLD, &status);

    end_time = MPI_Wtime(); // End the timer

    printf("Procesul cu rancul %d al nodului '%s' a primit valoarea %d de la procesul cu rancul %d\n",
           rank, processor_name, t, t);

    if (rank == 0)
        printf("Timpul de executie: %f secunde\n", end_time - start_time);

    MPI_Finalize();
    return 0;
}
