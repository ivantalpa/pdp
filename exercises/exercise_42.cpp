#include<mpi.h>
#include<stdio.h>
#include <cstdlib>
#include <ctime>


int main(int argc, char *argv[]) {
    int numtask, sendcount, reccount, source;
    int i, myrank, root=0;
    double *A_Init, *A_Fin;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtask);

    double Rows[numtask];

    sendcount = numtask;
    reccount = numtask;

    if (myrank == 0)
        printf("\n=====REZULTATUL PROGRAMULUI '%s' \n",argv[0]);

    MPI_Barrier(MPI_COMM_WORLD);

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
    } else {
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Scatter(A_Init, sendcount, MPI_DOUBLE, Rows, reccount, MPI_DOUBLE, root, MPI_COMM_WORLD);

    printf("\n");
    printf("Resultatele f-tiei MPI_Scatter pentru procesul cu rankul %d \n", myrank);

    for (i=0; i < numtask; ++i)
        printf("Rows[%d]=%5.2f ",i, Rows[i]);

    printf("\n");
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Gather(Rows, sendcount, MPI_DOUBLE, A_Fin, reccount, MPI_DOUBLE, root, MPI_COMM_WORLD);

    if(myrank == root) {
        printf("\n");
        printf("Resultatele f-tiei MPI_Gather ");

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

    MPI_Finalize();
    return 0;
}