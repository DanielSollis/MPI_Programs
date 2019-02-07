#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int token;
	if (rank != 0) {
		MPI_Recv(&token, 1,  MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("process %d received token %d from process %d\n", rank, token, rank -1);
	}
	else {
		//set token's value if you are rank 0
		token = -1;
	}
	MPI_Send(&token, 1, MPI_INT, (rank +1) % size, 0, MPI_COMM_WORLD);
	
	//now process 0 can receive from the last process
	if (rank == 0) {
		MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("process %d received token %d from process %d\n", rank, token, size -1);
	}
	MPI_Finalize();
	return 0;
}
