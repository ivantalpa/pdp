#include <mpi.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int size, reccount, source;
    double *A_Init, *A_Fin;
    int myrank, root=0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sendcounts[size], displs[size];
    int rows, cols;
    double *Rows;

    if (myrank == 0)
        printf("\n=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);

    MPI_Barrier(MPI_COMM_WORLD);

    if(myrank == root) {
        cout << "Introduceti numarul de rinduri: ";
        cin >> rows;
        cout << "Introduceti numarul de coloane: ";
        cin >> cols;

        A_Init = (double*) malloc(rows * cols * sizeof(double));
        A_Fin = (double*) malloc(rows * cols * sizeof(double));

        for(int i = 0; i < rows * cols; i++)
            A_Init[i] = rand() / 1000000000.0;

        printf("Matricea initiala\n");
        for(int i = 0; i < rows; i++) {
            printf("\n");
            for(int j = 0; j < cols; j++)
                printf("A_Init[%d,%d]=%5.2f ", i, j, A_Init[i * cols + j]);
        }
        printf("\n");
        MPI_Barrier(MPI_COMM_WORLD);
    } else {
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Bcast(&rows, 1, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Bcast(&cols, 1, MPI_INT, root, MPI_COMM_WORLD);

    int rinduriPeProces = rows / size;
    int rinduriRamase = rows % size;
    int deplasarea = 0;

    for (int i = 0; i < size; ++i) {
        displs[i] = deplasarea;
        if (i < rinduriRamase)
            sendcounts[i] = (rinduriPeProces + 1) * cols;
        else
            sendcounts[i] = rinduriPeProces * cols;

        deplasarea += sendcounts[i];
    }

    reccount = sendcounts[myrank];
    Rows = new double[reccount];

    MPI_Scatterv(A_Init, sendcounts, displs, MPI_DOUBLE, Rows, reccount, MPI_DOUBLE, root, MPI_COMM_WORLD);

    printf("\n");
    printf("Rezultatele f-tiei MPI_Scatterv pentru procesul cu rankul %d \n", myrank);
    for (int i = 0; i < reccount; ++i)
        printf(" Rows[%d]=%5.2f ", i, Rows[i]);

    printf("\n");
    cout << "\nProcesul " << myrank << " a primit " << reccount << " elemente (" << reccount / cols << " linii)" << endl;

    MPI_Barrier(MPI_COMM_WORLD);
    int sendcount = reccount;
    int *recvcounts = sendcounts;

    MPI_Gatherv(Rows, sendcount, MPI_DOUBLE, A_Fin, recvcounts, displs, MPI_DOUBLE, root, MPI_COMM_WORLD);

    if(myrank == root) {
        printf("\n");
        printf("Resultatele f-tiei MPI_Gatherv ");
        for(int i = 0; i < rows; i++) {
            printf("\n");
            for(int j = 0; j < cols; j++)
                printf("A_Fin[%d,%d]=%5.2f ", i, j, A_Fin[i * cols + j]);
        }
        printf("\n");
        MPI_Barrier(MPI_COMM_WORLD);
        free(A_Init);
        free(A_Fin);
    } else {
        MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Finalize();
    delete[] Rows;
    return 0;
}