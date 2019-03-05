#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <stdlib.h>
#include <cstdio>

int get_bigger(int first, int second);
int append_rank(int rank, int number);
int get_random_num(int rank, char even_or_odd);

int main(int argc, char *argv[]) {
	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	srand(time(NULL) * (rank + 1));
	
	int odd_num = get_random_num(rank, 'o');
	int even_num = get_random_num(rank, 'e');
	
	int  * numbers = (int *)malloc(2 * sizeof(int));
	numbers[0] = append_rank(rank, odd_num);
	numbers[1] = append_rank(rank, even_num);
	
	int  * sub_numbers = (int *)malloc(2 * sizeof(int));
	sub_numbers[0] = 0;
	sub_numbers[1] = 1;
	
	if (rank != 0) {
		MPI_Recv(sub_numbers, 2,  MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("rank%d:\n%d\n%d\nreceived:\n%d\n%d\n\n",
		 rank, numbers[0], numbers[1] , sub_numbers[0], sub_numbers[1]);
	}

	numbers[0] = get_bigger(numbers[0], sub_numbers[0]);
	numbers[1] = get_bigger(numbers[1], sub_numbers[1]);
	MPI_Send(numbers, 2, MPI_INT, (rank + 1 ) % size, 0, MPI_COMM_WORLD);
	
	//now process 0 can receive from the last process
	if (rank == 0) {
		MPI_Recv(sub_numbers, 2, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("rank %d:\n%d\n%d\nreceived:\n%d\n%d\n\n",
		 rank, numbers[0], numbers[1] , sub_numbers[0], sub_numbers[1]);
		printf("odd winner: %d\neven winner: %d\n", sub_numbers[0], sub_numbers[1]);
	}
	
	MPI_Finalize();
	return 0;
}


int get_bigger(int first, int second) {
	if (first > second) {
		return first;
	}
	return second;
}


int get_random_num(int rank, char even_or_odd) {
	int rand_odd = 0;
	int rand_even = 1;
	if (even_or_odd == 'o') {
		while (rand_odd % 2 == 0) {
			rand_odd = rand() % (99 + 1 - 10) + 10;
		}
		return rand_odd;
	}
	while (rand_even % 2 != 0) {
		rand_even = rand() % (99 + 1 - 10) + 10;
	}
	return rand_even;
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
