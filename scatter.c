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
	int to_scatter[10];
	int to_receive[2];
	if (rank == 0) {
		for (int i = 0; i < 10; i++) {
			to_scatter[i] = i + 1;
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Scatter(to_scatter, 2, MPI_INT, to_receive,  2, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	printf("rank %d received %d, %d\n", rank, to_receive[0], to_receive[1]);
	MPI_Finalize();
	return 0;
}
