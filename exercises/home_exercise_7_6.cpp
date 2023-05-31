#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <ctime>

int main(int argc, char *argv[]) {
    int size, rank;
    int dims[3], periods[3];
    MPI_Comm cube_comm, face_comm;
    MPI_Group face_group;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int namelen;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);

    if (rank == 0)
        printf("\n=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);

    MPI_Barrier(MPI_COMM_WORLD);

    // Create a 3D cube topology
    int n = cbrt(size);  // Assuming size is a perfect cube
    dims[0] = dims[1] = dims[2] = n;
    periods[0] = periods[1] = periods[2] = 1;  // All dimensions are periodic

    MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, 1, &cube_comm);

    if (cube_comm != MPI_COMM_NULL) {
        int coords[3];
        MPI_Cart_coords(cube_comm, rank, 3, coords);

        // Create a communicator for the processes on the same face of the cube
        int remain_dims[3] = {1, 1, 0};  // Remain only in x and y dimensions (assuming z dimension is the height of the cube)
        MPI_Cart_sub(cube_comm, remain_dims, &face_comm);

        if (face_comm != MPI_COMM_NULL) {
            int face_rank;
            MPI_Comm_rank(face_comm, &face_rank);
            printf("Sunt procesul cu rankul %d (%d) de pe nodul %s. Coordonatele mele in cub sunt (%d, %d, %d). Rankul meu pe fata cubului este %d. \n",
                   rank, rank, processor_name, coords[0], coords[1], coords[2], face_rank);
        }
    }

    MPI_Finalize();
    return 0;
}
