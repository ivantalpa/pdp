#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int world_size, *universe_sizep, flag, err[4], namelen, rank;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Comm everyone; /* intercommunicator */
    const int count = 3;
    int universe_size[count] = {8, 4, 3};
    const char* worker_program[count] = {"./exercise_10_2_spawn_worker1", "./exercise_10_2_spawn_worker2", "./exercise_10_2_spawn_worker3"};
    char **args[count];
    char *argv0[] = {NULL};
    char *argv1[] = {NULL};
    char *argv2[] = {NULL};
    args[0] = argv0;
    args[1] = argv1;
    args[2] = argv2;
    MPI_Info hostinfo[count];
    const char* host = "host";

    MPI_Init(&argc, &argv);
    MPI_Get_processor_name(processor_name, &namelen);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (int i = 0; i < count; i++)
        MPI_Info_create(&hostinfo[i]);

    MPI_Info_set(hostinfo[0], host, "compute-0-0, compute-0-1");
    MPI_Info_set(hostinfo[1], host, "compute-0-3");
    MPI_Info_set(hostinfo[2], host, "compute-0-11");

    if (world_size != 1)
        printf("Top heavy with management");

    printf("===I am Manager ('%s'), run on the node '%s' with rank %d and generate the following processes: \n", argv[0], processor_name, rank);

    for (int i = 0; i < count; i++)
    {
        printf("%d processes run the module '%s'\n", universe_size[i], worker_program[i]);
    }

    printf("===\n");

    MPI_Comm_spawn_multiple(count, const_cast<char**>(worker_program), args, universe_size, hostinfo, 0, MPI_COMM_SELF, &everyone, err);

    MPI_Finalize();
    return 0;
}
