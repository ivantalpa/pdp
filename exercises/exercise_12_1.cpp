#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, count, amode, i, j;
    MPI_File OUT;
    MPI_Aint rowsize;
    MPI_Datatype etype, ftype0, ftype1, ftype2;
    MPI_Status state;
    MPI_Datatype MPI_ROW;
    int blengths[2] = {0, 1};
    MPI_Datatype types[2];
    MPI_Aint disps[2];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    amode = MPI_MODE_DELETE_ON_CLOSE;
    MPI_File_open(MPI_COMM_WORLD, "array.dat", amode, MPI_INFO_NULL, &OUT);
    MPI_File_close(&OUT);

    amode = MPI_MODE_CREATE | MPI_MODE_RDWR;
    MPI_File_open(MPI_COMM_WORLD, "array.dat", amode, MPI_INFO_NULL, &OUT);

    MPI_Type_contiguous(8, MPI_INT, &MPI_ROW);
    MPI_Type_commit(&MPI_ROW);

    etype = MPI_ROW;
    ftype0 = MPI_ROW;
    types[0] = types[1] = MPI_ROW;
    disps[0] = (MPI_Aint) 0;
    MPI_Type_extent(MPI_ROW, &rowsize);
    disps[1] = 2 * rowsize;
    MPI_Type_struct(2, blengths, disps, types, &ftype1);
    MPI_Type_commit(&ftype1);

    disps[1] = 3 * rowsize;
    MPI_Type_struct(2, blengths, disps, types, &ftype2);
    MPI_Type_commit(&ftype2);

    count = 0;

    // Writing data in parallel to the "array.dat" file
    if (rank == 0) {
        int value0[2][8];

        for (i = 1; i <= 2; ++i) {
            for (j = 1; j <= 8; ++j) {
                value0[i-1][j-1] = 10 * i + j;
            }
        }

        MPI_File_set_view(OUT, 0, etype, ftype0, "native", MPI_INFO_NULL);
        MPI_File_write(OUT, &value0[rank][0], 2, MPI_ROW, &state);
        MPI_Get_count(&state, MPI_ROW, &count);

        printf("===Procesul %d a inscris in fisierul ""array.dat"" urmatoarele %d randuri:\n", rank, count);

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                printf("%d\t", value0[i][j]);
            }

            printf("\n");
        }
    }

    if (rank == 1) {
        int value1[8];

        for (j = 1; j <= 8; ++j) {
            value1[j-1] = 10 * 3 + j;
        }

        MPI_File_set_view(OUT, 0, etype, ftype1, "native", MPI_INFO_NULL);
        MPI_File_write(OUT, &value1, 1, MPI_ROW, &state);
        MPI_Get_count(&state, MPI_ROW, &count);

        printf("===Procesul %d a inscris in fisierul ""array.dat"" urmatoarle %d randuri\n", rank, count);

        for (int j = 0; j < 8; j++) {
            printf("%d\t", value1[j]);
        }

        printf("\n");
    }

    if (rank == 2) {
        int value2[8];

        for (j = 1; j <= 8; ++j) {
            value2[j-1] = 10 * 4 + j;
        }

        MPI_File_set_view(OUT, 0, etype, ftype2, "native", MPI_INFO_NULL);
        MPI_File_write(OUT, &value2, 1, MPI_ROW, &state);
        MPI_Get_count(&state, MPI_ROW, &count);

        printf("===Procesul %d a inscris in fisierul ""array.dat"" urmatoarele %d randuri\n", rank, count);

        for (int j = 0; j < 8; j++) {
            printf("%d\t", value2[j]);
        }

        printf("\n");
    }

    // Reading data in parallel from the "array.dat" file
    if (rank == 3) {
        int myval3[2][8];

        MPI_File_set_view(OUT, 0, etype, ftype0, "native", MPI_INFO_NULL);
        MPI_File_read(OUT, &myval3[0][0], 2, MPI_ROW, &state);
        MPI_Get_count(&state, MPI_ROW, &count);

        printf("---Procesul %d a citit din fisierul ""array.dat"" urmatoarele %d rinduri\n", rank, count);

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                printf("%d\t", myval3[i][j]);
            }

            printf("\n");
        }
    }

    if (rank == 4) {
        int myval4[8];

        MPI_File_set_view(OUT, 0, etype, ftype1, "native", MPI_INFO_NULL);
        MPI_File_read(OUT, &myval4, 1, MPI_ROW, &state);
        MPI_Get_count(&state, MPI_ROW, &count);

        printf("---Procesul %d a citit din fisierul ""array.dat"" urmatoarele %d rinduri\n", rank, count);

        for (int j = 0; j < 8; j++) {
            printf("%d\t", myval4[j]);
        }

        printf("\n");
    }

    if (rank == 5) {
        int myval5[8];

        MPI_File_set_view(OUT, 0, etype, ftype2, "native", MPI_INFO_NULL);
        MPI_File_read(OUT, &myval5, 1, MPI_ROW, &state);
        MPI_Get_count(&state, MPI_ROW, &count);

        printf("---Procesul %d a citit din fisierul ""array.dat"" urmatoarele %d rinduri\n", rank, count);

        for (int j = 0; j < 8; j++) {
            printf("%d\t", myval5[j]);
        }

        printf("\n");
    }

    MPI_File_close(&OUT);
    MPI_Finalize();

    return 0;
}