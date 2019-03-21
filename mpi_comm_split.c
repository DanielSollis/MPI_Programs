#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	MPI_Init(&argc, &argv);
	int size, rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	MPI_Comm new_comm;
	int color = rank / 4;
	int key = rank;

	MPI_Comm_split(MPI_COMM_WORLD, color, key, &new_comm);

	int new_rank, new_size;
	MPI_Comm_rank(new_comm, &new_rank);
	MPI_Comm_size(new_comm, &new_size);

	printf("Original rank/size: %d/%d, New rank/size: %d/%d\n", 
		rank, size, new_rank, new_size);

	MPI_Finalize();
	return 0;
}
