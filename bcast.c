#include <mpi.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int rand_num = 0;
	if (rank == 0) {
		srand(time(NULL));
		rand_num = rand() % 100;
		printf("original num: %d\n", rand_num);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&rand_num, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if (rank != 0) {
		printf("rank %d received num: %d\n", rank, rand_num);
	}
	MPI_Finalize();
	return 0;
}
