#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]) {
    int rank, test_rank = 2;
    int size;
    int ndims = 3;
    int source, dest;
    int up_y, right_y, right_x, left_x, up_z, down_z;
    int dims[3] = {0, 0, 0}, coords[3] = {0, 0, 0};
    int coords_left_x[3] = {0, 0, 0}, coords_right_x[3] = {0, 0, 0},
        coords_left_y[3] = {0, 0, 0}, coords_right_y[3] = {0, 0, 0}, coords_up_z[3] = {0, 0, 0}, coords_down_z[3] = {0, 0, 0};
    int periods[3] = {0, 0, 0}, reorder = 0;
    MPI_Comm comm;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Dims_create(size, ndims, dims);

    if (rank == 0) {
        printf("\n=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);
        for (int i = 0; i < 3; i++)
            cout << "Numarul de procese pe axa " << i << " este " << dims[i] << "; ";
        cout << endl;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &comm);
    MPI_Cart_coords(comm, rank, ndims, coords);

    sleep(rank);

    cout << "Procesul cu rankul " << rank << " are coordonatele (" << coords[0] << "," << coords[1] << ","
         << coords[2] << ")" << endl;

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == test_rank) {
        printf("Sunt procesul cu rankul %d (%d,%d,%d) vecinii mei sunt: \n", rank, coords[0], coords[1], coords[2]);

        MPI_Cart_shift(comm, 0, 1, &left_x, &right_x);
        if (left_x < 0) {
            coords_left_x[0] = -1;
            coords_left_x[1] = -1;
            coords_left_x[2] = -1;
        } else {
            MPI_Cart_coords(comm, left_x, ndims, coords_left_x);
        }

        if (right_x < 0) {
            coords_right_x[0] = 1;
            coords_right_x[1] = 1;
            coords_right_x[2] = 1;
        } else {
            MPI_Cart_coords(comm, right_x, ndims, coords_right_x);
        }

        printf(" pe directia axei X : stanga %d(%d,%d,%d) dreapta %d(%d,%d,%d) \n",
               left_x, coords_left_x[0], coords_left_x[1], coords_left_x[2], right_x,
               coords_right_x[0], coords_right_x[1], coords_right_x[2]);

        MPI_Cart_shift(comm, 1, 1, &up_y, &right_y);
        if (up_y < 0) {
            coords_left_y[0] = -1;
            coords_left_y[1] = -1;
            coords_left_y[2] = 1;
        } else {
            MPI_Cart_coords(comm, up_y, ndims, coords_left_y);
        }

        if (right_y < 0) {
            coords_right_y[0] = -1;
            coords_right_y[1] = -1;
            coords_right_y[2] = -1;
        } else {
            MPI_Cart_coords(comm, right_y, ndims, coords_right_y);
        }

        printf(" pe directia axei Y : stanga %d(%d,%d,%d) dreapta %d(%d,%d,%d) \n",
               up_y, coords_left_y[0], coords_left_y[1], coords_left_y[2], right_y,
               coords_right_y[0], coords_right_y[1], coords_right_y[2]);

        MPI_Cart_shift(comm, 2, 1, &up_z, &down_z);
        if (up_z < 0) {
            coords_up_z[0] = -1;
            coords_up_z[1] = -1;
            coords_up_z[2] = -1;
        } else {
            MPI_Cart_coords(comm, up_z, ndims, coords_up_z);
        }

        if (down_z < 0) {
            coords_down_z[0] = -1;
            coords_down_z[1] = -1;
            coords_down_z[2] = -1;
        } else {
            MPI_Cart_coords(comm, down_z, ndims, coords_down_z);
        }

        printf(" pe directia axei Z : jos %d(%d,%d,%d) sus %d(%d,%d,%d) \n",
               up_z, coords_up_z[0], coords_up_z[1], coords_up_z[2], down_z,
               coords_down_z[0], coords_down_z[1], coords_down_z[2]);

        printf("Valorile negative semnifica lipsa procesului vecin!\n");
    }

    MPI_Finalize();
    return 0;
}