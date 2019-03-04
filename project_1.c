#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <stdlib.h>
#include <cstdio>

int append_rank(int rank, int number);

int main(int argc, char *argv[]) {
	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int token;
	if (rank != 0) {
		MPI_Recv(&token, 2,  MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		//printf("process %d received token %d from process %d\n", rank, token, rank -1);
	}
	else {
		//set token's value if you are rank 0
		token = -1;
	}

	
	srand(time(NULL) * rank);
	int rand_odd = 0;
	int rand_even = 1;
	
	while (rand_odd % 2 == 0) {
		rand_odd = (rand() + 10) % 100;
	}
	while (rand_even % 2 != 0) {
		rand_even = (rand() + 10) % 100;
	}
	int numbers[2] = {append_rank(rank, rand_odd), append_rank(rank, rand_even)};
		
	printf("%d\n%d\n\n", numbers[0], numbers[1]);
	printf("odd: %d\n, even: %d\n\n", numbers[0], numbers[1]);


	MPI_Send(&token, 1, MPI_INT, (rank +1) % size, 0, MPI_COMM_WORLD);
	//now process 0 can receive from the last process
	if (rank == 0) {
		MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("process %d received token %d from process %d\n", rank, token, size -1);
	}
	MPI_Finalize();
	return 0;
}
int append_rank(int rank, int number) {
	char rank_str[5];
	if (rank > 9) {
		sprintf(rank_str, "%d%d", rank, number);
	}
	else {
		sprintf(rank_str, "1%d%d", rank, number);
	}
	return atoi(rank_str);
}
