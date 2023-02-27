#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) 
    {
    int size, rank, i, j, m;
    double begin,end,max,min;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int load[size];
    j = rank;

    begin = MPI_Wtime();

    for (i = 0; i < size; i++)
        MPI_Send(&j, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    for (i = 0; i < size; i++)
        MPI_Recv(&load[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    end = MPI_Wtime();

    printf("Processes %d: ", rank);
    for (m = 0; m < size; m++)
        printf(" %d", load[m]);
        printf("\n");

    MPI_Finalize();
    if (min > begin) 
    {
        min = begin;
    }

    if (max < end) 
    {
        max = end;
    }
    if (rank == 0)
    {
        printf("\nTotal time: %.6f\n", max - min);
    }
    return 0;
}
