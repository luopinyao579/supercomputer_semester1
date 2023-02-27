#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <mpi.h>

#define N1 3                   
#define N2 4                    
#define N3 3                  
#define MASTER 0               
#define FROM_MASTER 1           
#define FROM_WORKER 2          

int main(int argc, char *argv[]) 
{
    int size,rank,numberWorkers,source,dest,messageType,                
    rows,averow, extra, offset,i, j, k, s;                
    double A[N1][N2],           
    B[N2][N3],                  
    C[N1][N3];                  
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size < 2) 
    {
        printf("Need at least two MPI tasks. Quitting.\n");
        MPI_Abort(MPI_COMM_WORLD, s);
        exit(1);
    }
    numberWorkers = size - 1;

    if (rank == MASTER) 
    {
        std::ifstream in("process.txt");

        printf("Program has started with %d tasks.\n", size);
        printf("Initialization arrays.\n");
        for (i = 0; i < N1; i++)
            for (j = 0; j < N2; j++)
                in >> A[i][j];
        for (i = 0; i < N2; i++)
            for (j = 0; j < N3; j++)
                in >> B[i][j];

        in.close();

        printf("Matrix A:\n");
        for (i = 0; i < N1; i++) 
       {
            for (j = 0; j < N2; j++)
                printf("%6.2f\t", A[i][j]);
            printf("\n");
        }

        printf("\n\nMatrix B:\n");
        for (i = 0; i < N2; i++) 
	{
            for (j = 0; j < N3; j++)
                printf("%6.2f\t", B[i][j]);
            printf("\n");
        }

        printf("\nA * B = C\n\n");

        double start = MPI_Wtime();

        averow = N1 / numberWorkers;
        extra = N1 % numberWorkers;
        offset = 0;
        messageType = FROM_MASTER;
        for (dest = 1; dest <= numberWorkers; dest++) 
	{
            rows = (dest <= extra) ? averow + 1 : averow;
            printf("Send the %d rows to task %d offset=%d.\n", rows, dest, offset);
            MPI_Send(&offset, 1, MPI_INT, dest, messageType, MPI_COMM_WORLD);
            MPI_Send(&rows, 1, MPI_INT, dest, messageType, MPI_COMM_WORLD);
            MPI_Send(&A[offset][0], rows * N2, MPI_DOUBLE, dest, messageType,MPI_COMM_WORLD);
            MPI_Send(&B, N2 * N3, MPI_DOUBLE, dest, messageType, MPI_COMM_WORLD);
            offset = offset + rows;
        }

        messageType = FROM_WORKER;
        for (i = 1; i <= numberWorkers; i++) 
	{
            source = i;
            MPI_Recv(&offset, 1, MPI_INT, source, messageType, MPI_COMM_WORLD, &status);
            MPI_Recv(&rows, 1, MPI_INT, source, messageType, MPI_COMM_WORLD, &status);
            MPI_Recv(&C[offset][0], rows * N3, MPI_DOUBLE, source, messageType,MPI_COMM_WORLD, &status);
            printf("Received results from task %d.\n", source);
        }

        printf("\nMatrix C:\n");
        std::ofstream out("result.txt");

        for (i = 0; i < N1; i++) 
	{
            for (j = 0; j < N3; j++) 
	    {
                printf("%6.2f   ", C[i][j]);
                out << C[i][j];
                if (j + 1 < N3) out << " ";
            }
            printf("\n");
            out << "\n";
        }

        out.close();

        double end = MPI_Wtime();
        printf("Finished in %f s.\n", end - start);
    }

    if (rank > MASTER) 
	   {
		messageType = FROM_MASTER;
		MPI_Recv(&offset, 1, MPI_INT, MASTER, messageType, MPI_COMM_WORLD, &status);
		MPI_Recv(&rows, 1, MPI_INT, MASTER, messageType, MPI_COMM_WORLD, &status);
		MPI_Recv(&A, rows * N2, MPI_DOUBLE, MASTER, messageType, MPI_COMM_WORLD, &status);
		MPI_Recv(&B, N2 * N3, MPI_DOUBLE, MASTER, messageType, MPI_COMM_WORLD, &status);

		for (k = 0; k < N3; k++)
		    for (i = 0; i < rows; i++) 
			{
				C[i][k] = 0.0;
				for (j = 0; j < N2; j++)
				    C[i][k] = C[i][k] + A[i][j] * B[j][k];
                	}
        messageType = FROM_WORKER;
        MPI_Send(&offset, 1, MPI_INT, MASTER, messageType, MPI_COMM_WORLD);
        MPI_Send(&rows, 1, MPI_INT, MASTER, messageType, MPI_COMM_WORLD);
        MPI_Send(&C, rows * N3, MPI_DOUBLE, MASTER, messageType, MPI_COMM_WORLD);
    }
    MPI_Finalize();  
return 0;
}
