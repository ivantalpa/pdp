#include<mpi.h>
#include<stdio.h>
#include <cstdlib>
#include <ctime>


int main(int argc, char *argv[]) {
    int numtask, sendcount, reccount, source;
    int i, myrank, root=0;
    int mb, nb; // block dimensions
    double *A_Init, *A_Fin;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtask);

    mb = numtask; // adjust based on the actual block size
    nb = numtask; // adjust based on the actual block size

    double Blocks[mb][nb];

    int *sendcounts = (int*) malloc(numtask * sizeof(int));
    int *displs = (int*) malloc(numtask * sizeof(int));

    if(myrank == root) {
        A_Init = (double*) malloc(numtask * numtask * sizeof(double));
        A_Fin = (double*) malloc(numtask * numtask * sizeof(double));

        for(int i=0; i < numtask * numtask; i++)
            A_Init[i] = rand() / 1000000000.0;

        printf("Tipar datele initiale\n");

        for(int i=0; i < numtask; i++) {
            printf("\n");
            for(int j=0; j < numtask; j++)
                printf("A_Init[%d,%d]=%5.2f ",i,j, A_Init[i*numtask+j]);
        }

        printf("\n");
        MPI_Barrier(MPI_COMM_WORLD);

        for(int i=0; i < numtask; i++) {
            sendcounts[i] = mb * nb;
            displs[i] = i * mb * nb;
        }
    } else {
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Scatterv(A_Init, sendcounts, displs, MPI_DOUBLE, Blocks, mb*nb, MPI_DOUBLE, root, MPI_COMM_WORLD);

    printf("\n");
    printf("Resultatele f-tiei MPI_Scatterv pentru procesul cu rankul %d \n", myrank);

    for (i=0; i < mb; ++i)
        for (int j=0; j < nb; ++j)
            printf("Blocks[%d,%d]=%5.2f ",i, j, Blocks[i][j]);

    printf("\n");
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Gatherv(Blocks, mb*nb, MPI_DOUBLE, A_Fin, sendcounts, displs, MPI_DOUBLE, root, MPI_COMM_WORLD);

    if(myrank == root) {
        printf("\n");
        printf("Resultatele f-tiei MPI_Gatherv ");

        for(int i=0; i < numtask; i++) {
            printf("\n");
            for(int j=0; j < numtask; j++)
                printf("A_Fin[%d,%d]=%5.2f ",i,j, A_Fin[i*numtask+j]);
        }

        printf("\n");
        MPI_Barrier(MPI_COMM_WORLD);
    } else {
        MPI_Barrier(MPI_COMM_WORLD);
    }

    free(sendcounts);
    free(displs);

    MPI_Finalize();
    return 0;
}
