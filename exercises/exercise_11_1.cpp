#include "mpi.h"
#include <stdio.h>
#include <math.h>

typedef struct {
    float position[3];
    float mass;
} Particle;

MPI_Datatype MPI_Particle;

void construct_datatypes(void) {
    Particle p;
    int blens[2];
    MPI_Aint displ[2];
    MPI_Datatype types[2];

    blens[0] = 3;
    types[0] = MPI_FLOAT;
    displ[0] = (MPI_Aint) &p.position - (MPI_Aint) &p;

    blens[1] = 1;
    types[1] = MPI_FLOAT;
    displ[1] = (MPI_Aint) &p.mass - (MPI_Aint) &p;

    MPI_Type_struct(2, blens, displ, types, &MPI_Particle);
    MPI_Type_commit(&MPI_Particle);

    return;
}

int main(int argc, char *argv[]) {
    int nProc, myRank, i;
    Particle *myP;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    construct_datatypes();

    if (myRank == 0)
        printf("\n=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);

    MPI_Barrier(MPI_COMM_WORLD);

    myP = (Particle *) calloc(nProc, sizeof(Particle));

    if (myRank == 0) {
        for (i = 0; i < nProc; i++) {
            myP[i].position[0] = i;
            myP[i].position[1] = i + 1;
            myP[i].position[2] = i + 2;
            myP[i].mass = 10 + 100.0 * rand() / RAND_MAX;
        }
    }

    MPI_Bcast(myP, nProc, MPI_Particle, 0, MPI_COMM_WORLD);

    printf("Proces rank %d: pozitia particuleei (%f, %f, %f) masa ei %f\n", myRank, myP[myRank].position[0],
           myP[myRank].position[1], myP[myRank].position[2], myP[myRank].mass);

    MPI_Finalize();

    return 0;
}
