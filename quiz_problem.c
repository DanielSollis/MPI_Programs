#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_numbers(int rank, int size, int number, int * arr);
int get_interest(int rank, int size, int num, int * arr);
void print_results(int rank, int interest);


int main(int argc, char * argv[]) {
	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	srand(time(NULL) * (rank + 1));
	int rand_num = rand() % 99 + 1;
	int * rand_arr = (int *)malloc(size * sizeof(int));
	MPI_Allgather(&rand_num, 1, MPI_INT, rand_arr, 1, MPI_INT, MPI_COMM_WORLD);
	print_numbers(rank, size, rand_num, rand_arr);
	
	int interest = get_interest(rank, size, rand_num, rand_arr);
	print_results(rank, interest);
	free(rand_arr);
	MPI_Finalize();
	return 0;
}


void print_numbers(int rank, int size, int number, int * arr) {
	printf("rank %d: %d\n", rank, number);
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) {
		printf("gathered numbers: ");
		for (int i = 0; i < size; i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
	}
}

int get_interest(int rank, int size, int num, int * arr) {
	int interest = 0;
	int best = 10000;
	arr[rank] = 10000;
	for (int i = 0; i < size; i++) {
		arr[i] = abs(arr[i] - num);
		if (arr[i] < best) {
			interest = i;
			best = arr[i];
		}
	}
	return interest;
}

void print_results(int rank, int interest) {
	if (rank == 0) {
		printf("\n\n");
	}
	MPI_Barrier(MPI_COMM_WORLD);
	printf("rank %d interest: %d\n", rank, interest);
}