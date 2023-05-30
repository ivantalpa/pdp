#include <stdio.h>
#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]) {
    int size, rank, t, namelen;
    int incep = 9;  // Modified value for incep, now an odd number
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);

    if (rank == 0)
        printf("\n=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);

    if (size % 2 != 0)
         size = size - 1;  // Make size odd to match odd-rank processes

    if (rank % 2 != 0) {  // Only odd-ranked processes participate in communication
        if (rank == incep) {
            MPI_Send(&rank, 1, MPI_INT, (rank + size - 2) % size, 10, MPI_COMM_WORLD);
            MPI_Recv(&t, 1, MPI_INT, (rank + 2) % size, 10, MPI_COMM_WORLD, &status);
        } else {
            MPI_Recv(&t, 1, MPI_INT, (rank + 2) % size, 10, MPI_COMM_WORLD, &status);
            MPI_Send(&rank, 1, MPI_INT, (rank + size - 2) % size, 10, MPI_COMM_WORLD);
        }

        printf("Procesul cu rankul %d al nodului '%s' a primit valoarea %d de la procesul cu rankul %d\n",
               rank, processor_name, t, t);
    }

    MPI_Finalize();
    return 0;
}
