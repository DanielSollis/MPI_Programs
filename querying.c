#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	const int MAX_NUMBERS = 100;
	int numbers[MAX_NUMBERS];
	int number_amount;
	if (rank == 0) {
		// pick random amount of ints to send to one process
		srand(time(NULL));
		number_amount = (rand()/(float)RAND_MAX) * MAX_NUMBERS;
		
		//send the amount of ints to process one
		MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("0 sent %d numbers to 1\n", number_amount);
	}
	else if(rank == 1) {
		MPI_Status status;
		//receive at most MAX_NUMBERS from process zero
		MPI_Recv(numbers, MAX_NUMBERS, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		//After receiving the message, check the status to determine how many numbers were received
		MPI_Get_count(&status, MPI_INT, &number_amount);
		//print off the amount of numbers and also additional info in the status object
		printf("1 received %d numbers from 0. message source = %d, tag = %d\n", number_amount, status.MPI_SOURCE, status.MPI_TAG);
	}	
	MPI_Finalize();
	return 0;
}
