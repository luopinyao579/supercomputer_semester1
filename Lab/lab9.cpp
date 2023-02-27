#include<cstdio>
#include<vector>
#include<algorithm>
#include<mpi.h>

int main(int argc ,char**argv)
{
	int size,rank;
	MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int d=0;
	std::vector<int> offers ={212,324,433};
	std::vector<int> result;

	printf("\n Process %d of %d \n",rank,size);
	if (rank !=0)	
	{
		d = offers.at(rank - 1);
		printf("F%d: input your price: %d\n", rank, d);
		printf("F%d: Sending to F%d = %d\n", rank, 0, d);
		MPI_Send(&d, 1, MPI_INT, 0, 5, MPI_COMM_WORLD);
	}
	else
	{
	for(int i=1; i<size; ++i)
		{
			MPI_Recv(&d, 1, MPI_INT, i, 5, MPI_COMM_WORLD, &status);
            		printf("F%d: Received from F%d = %d\n", rank, i, d);
            		result.push_back(d);
		}
	
	for(int i = 0;i<result.size(); ++i)
	{
		printf("F%d:offer from F%d =%d\n",rank,i,result.at(i));
	}	
