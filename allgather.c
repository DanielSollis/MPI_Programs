#include <mpi.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int * numbers = (int *)malloc(sizeof(int) * size);
	srand(time(NULL) * rank);
	int rand_num = rand() % 100;
	
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Allgather(&rand_num, 1, MPI_INT, numbers, 1, MPI_INT, MPI_COMM_WORLD);
	
	printf("rank %d received numbers: ", rank);
	for (int i = 0; i < size; i++) {
		printf("%d ", numbers[i]);
	}
	printf("\n");

	MPI_Finalize();
	return 0;
}
