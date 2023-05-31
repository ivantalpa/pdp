#include <stdio.h>
#include "mpi.h"
#include <cstring>
#ifdef _OPENMP
#include <omp.h>
#define TRUE 1
#define FALSE 0
#else
#define omp_get_thread_num() 0
#endif

int main(int argc, char *argv[]) {
    #ifdef _OPENMP
    (void) omp_set_dynamic(FALSE);
    if (omp_get_dynamic()) {
        printf("Warning: dynamic adjustment of threads has been set\n");
    }
    (void) omp_set_num_threads(4);
    #endif

    int numprocs, realnumprocs, rank, namelen, mpisupport;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int iam = 0, np = 1;
    omp_lock_t lock;
    omp_init_lock(&lock);

    MPI_Init(&argc, &argv);
    MPI_Get_processor_name(processor_name, &namelen);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (strcmp(processor_name, "compute-0-0.local") == 0) {
        omp_set_num_threads(4);
        #pragma omp parallel default(shared) private(iam, np, realnumprocs)
        {
            np = omp_get_num_threads();
            realnumprocs = omp_get_num_procs();
            iam = omp_get_thread_num();

            omp_set_lock(&lock);

            #pragma omp master
            {
                printf("\n");
                printf(" ===Procesul MPI cu rankul %d al nodului cu numele '%s' a executat %d fire ===\n", rank, processor_name, omp_get_num_threads());
            }

            printf("Hello from thread number %d, total number of threads are %d, MPI process rank is %d, real number of processors is %d on node %s\n", iam, np, rank, realnumprocs, processor_name);

            omp_unset_lock(&lock);
        }

        omp_destroy_lock(&lock);
        MPI_Barrier(MPI_COMM_WORLD);
    }
    else {
        if (strcmp(processor_name, "compute-0-1.local") == 0) {
            omp_set_num_threads(2);
            #pragma omp parallel default(shared) private(iam, np, realnumprocs)
            {
                np = omp_get_num_threads();
                realnumprocs = omp_get_num_procs();
                iam = omp_get_thread_num();

                omp_set_lock(&lock);

                #pragma omp master
                {
                    printf("\n");
                    printf(" ===Procesul MPI cu rankul %d al nodului cu numele '%s' a executat %d fire ===\n", rank, processor_name, omp_get_num_threads());
                }

                omp_unset_lock(&lock);

                printf("Hello from thread number %d, total number of threads are %d, MPI process rank is %d, real number of processors is %d on node %s\n", iam, np, rank, realnumprocs, processor_name);

                omp_unset_lock(&lock);
            }

            omp_destroy_lock(&lock);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}
