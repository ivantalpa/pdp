#include<mpi.h>
#include<stdio.h>
#include <cstdlib>
#include <ctime>
#include <cstring>


int main(int argc, char *argv[]) {
    int numtask, sendcount, reccount, source;
    int i, j, myrank, root=0;
    double *A_Init, *A_Fin;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtask);

    double Row[numtask];

    sendcount = numtask;
    reccount = numtask;

    if (myrank == 0)
        printf("\n=====REZULTATUL PROGRAMULUI '%s' \n",argv[0]);

    MPI_Barrier(MPI_COMM_WORLD);

    if(myrank == root) {
        A_Init = (double*) malloc(numtask * numtask * sizeof(double));
        A_Fin = (double*) malloc(numtask * numtask * sizeof(double));

        for(i=0; i < numtask * numtask; i++)
            A_Init[i] = rand() / 1000000000.0;

        printf("Tipar datele initiale\n");

        for(i=0; i < numtask; i++) {
            printf("\n");
            for(j=0; j < numtask; j++)
                printf("A_Init[%d,%d]=%5.2f ",i,j, A_Init[i*numtask+j]);
        }

        printf("\n");
        MPI_Barrier(MPI_COMM_WORLD);

        for(i=1; i<numtask; i++){
            MPI_Sendrecv(&A_Init[i*numtask], numtask, MPI_DOUBLE, i, 0, &A_Fin[i*numtask], numtask, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        memcpy(&A_Fin[0], &A_Init[0], numtask*sizeof(double));
    } else {
        MPI_Sendrecv(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL, root, 0, Row, numtask, MPI_DOUBLE, root, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Barrier(MPI_COMM_WORLD);
    }

    printf("\n");
    printf("Resultatele functiei MPI_Sendrecv pentru procesul cu rankul %d \n", myrank);

    for (i=0; i < numtask; ++i)
        printf("Row[%d]=%5.2f ",i, Row[i]);

    printf("\n");
    MPI_Barrier(MPI_COMM_WORLD);

    if(myrank == root) {
        printf("\n");
        printf("Resultatele functiei MPI_Sendrecv ");

        for(i=0; i < numtask; i++) {
            printf("\n");
            for(j=0; j < numtask; j++)
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
