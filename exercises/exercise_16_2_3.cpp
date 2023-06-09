#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#define TRUE 1
#define FALSE 0
#else
#define omp_get_thread_num() 0
#endif

double f(double y) {
    return (4.0 / (1.0 + y * y));
}

int main(int argc, char *argv[]) {
    int i, p, k = 0, size, rank, rank_new;
    double PI25DT = 3.141592653589793238462643;
    int Node_rank;
    int Nodes; // numarul de noduri
    int local_rank = atoi(getenv("OMPI_COMM_WORLD_LOCAL_RANK"));
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;
    MPI_Comm com_new, ring1;
    MPI_Group MPI_GROUP_WORLD, newgr;
    int *ranks, *newGroup;
    int namelen;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);

    if (rank == 0)
        printf("=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);

    MPI_Barrier(MPI_COMM_WORLD);

    if (local_rank == 0)
        k = 1;

    MPI_Allreduce(&k, &Nodes, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    newGroup = (int *)malloc(Nodes * sizeof(int));
    ranks = (int *)malloc(size * sizeof(int));

    int r;

    if (local_rank == 0)
        ranks[rank] = rank;
    else
        ranks[rank] = -1;

    for (int i = 0; i < size; ++i)
        MPI_Bcast(&ranks[i], 1, MPI_INT, i, MPI_COMM_WORLD);

    for (int i = 0, j = 0; i < size; ++i) {
        if (ranks[i] != -1) {
            newGroup[j] = ranks[i];
            ++j;
        }
    }

    MPI_Comm_group(MPI_COMM_WORLD, &MPI_GROUP_WORLD);
    MPI_Group_incl(MPI_GROUP_WORLD, Nodes, newGroup, &newgr);
    MPI_Comm_create(MPI_COMM_WORLD, newgr, &com_new);
    MPI_Group_rank(newgr, &rank_new);

    if (rank_new != MPI_UNDEFINED) {
        double w, x, sum, pi, Final_pi, a, b;
        int i, MPIrank;
        int n = 1000000;

        w = 1.0 / n;
        sum = 0.0;
        a = (rank_new + 0.0) / Nodes;
        b = (rank_new + 1.0) / Nodes;
        omp_set_num_threads(2);

#pragma omp parallel private(x) shared(w) reduction(+:sum)
        {
            if (rank_new == 0)
#pragma omp master
            {
                printf("Pentru fiecare proces MPI se genereaza %d procese OpenMP (fire)\n", omp_get_num_threads());
            }

#pragma omp for nowait
            for (i = 0; i < n; i++) {
                // x = w * (i - 0.5);
                x = a + (b - a) * w * (i - 0.5);
                sum = sum + f(x);
            }
        }

        pi = (b - a) * w * sum;
        sleep(rank_new);
        printf("Procesul %d al comunicatorului 'com_new' de pe nodul %s a calculat valoarea pi=%f pe [%f,%f].\n", rank_new, processor_name, pi, a, b);

        MPI_Barrier(com_new);
        MPI_Reduce(&pi, &Final_pi, 1, MPI_DOUBLE, MPI_SUM, 0, com_new);

        if (rank_new == 0) {
            printf("Valoarea finala este %.16f, Error is %.16f\n", Final_pi, fabs(Final_pi - PI25DT));
        }
    }

    MPI_Finalize();
    return 0;
}
