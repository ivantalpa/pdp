#include <stdio.h>
#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]) {
    int size, rank, t, namelen;
    int incep = 0; // Process that will send messages
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);

    if (rank == 0)
        printf("\n=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);

    for (int i = 1; i < size; i++) {
        if (rank == incep) {
            MPI_Sendrecv(&rank, 1, MPI_INT, i, 10,
                        &t, 1, MPI_INT, i, 10, MPI_COMM_WORLD, &status);
        } else if (rank == i) {
            MPI_Sendrecv(&rank, 1, MPI_INT, incep, 10,
                        &t, 1, MPI_INT, incep, 10, MPI_COMM_WORLD, &status);

            printf("Procesul cu rancul %d al nodului '%s' a primit valoarea %d de la procesul cu rancul %d\n",
                    rank, processor_name, t, incep);
        }
    }

    MPI_Finalize();
    return 0;
}
