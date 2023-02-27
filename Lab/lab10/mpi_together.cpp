#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) 
{
    int size, rank, j, m;
    double begin, end ,max,min;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int load[size];
    j = rank;
     
    begin =MPI_Wtime();

    MPI_Allgather(&j, 1, MPI_INT, load, 1, MPI_INT, MPI_COMM_WORLD);

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
        printf("\nTotal time: %.8f\n", max - min);
    }

    return 0;
}
