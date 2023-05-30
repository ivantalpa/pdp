#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the number of processes

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process

    int dataPerProcess = 10; // Assuming we have 10 pieces of data per process
    int* sendData = NULL;
    if (rank == 0) {
        sendData = new int[size * dataPerProcess];
        for (int i = 0; i < size * dataPerProcess; ++i) {
            sendData[i] = i;
        }
    }

    int* recvData = new int[dataPerProcess];

    MPI_Scatter(sendData, dataPerProcess, MPI_INT, recvData, dataPerProcess, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Data received by process %d: ", rank);
    for (int i = 0; i < dataPerProcess; ++i) {
        printf("%d ", recvData[i]);
    }
    printf("\n");

    delete[] recvData;
    if (rank == 0) {
        delete[] sendData;
    }

    MPI_Finalize(); // Finalize the MPI environment
    return 0;
}
