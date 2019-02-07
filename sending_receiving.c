#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int number;
     	if (rank == 0) {
           	number = -1;
           	//MPI_Send(start, count, datatype, dest, tag, comm)
		MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
           	printf("Process 0 sent number %d to process  1\n", number);
     	}
	else if (rank == 1) {
        	//MPI_Recv(start, count, datatype, source, tag, comm, status), status contains further info 
		MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         	printf("Process 1 received number %d from process 0\n", number);
     	}
	MPI_Finalize();
	return 0;
}
