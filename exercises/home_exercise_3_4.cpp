#include <stdio.h>
#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]) {
    int size, rank, t, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);

    if (rank == 0) {
        printf("\n=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);

        for(int i=1; i<size; i++) {
            MPI_Send(&rank, 1, MPI_INT, i, 10, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&t, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        printf("Procesul cu rancul %d al nodului '%s' a primit valoarea %d de la procesul cu rancul 0\n",
           rank, processor_name, t);
    }

    MPI_Finalize();
    return 0;
}
