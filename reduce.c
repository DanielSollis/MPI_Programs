#include <mpi.h>
#include <stdio.h>
#include <time.h>

const int ARR_SIZE = 5;

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int * numbers = (int *)malloc(sizeof(int) * ARR_SIZE);
	for (int i = 0; i < ARR_SIZE; i++) {
		numbers[i] = (i * (rank + 1));
	}

	for (int i = 0; i < size; i++) {
		if (rank == i) {
			printf("rank %d numbers: ", rank); 
			for (int j = 0; j < ARR_SIZE; j++) {
				printf("%d ", numbers[j]);
			}
			printf("\n");
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);

	int * max_result = (int *)malloc(sizeof(int) * ARR_SIZE);
	int * min_result = (int *)malloc(sizeof(int) * ARR_SIZE);
	int * sum_result = (int *)malloc(sizeof(int) * ARR_SIZE);
	int * prod_result = (int *)malloc(sizeof(int) * ARR_SIZE);

	MPI_Reduce(numbers, max_result, ARR_SIZE, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	MPI_Reduce(numbers, min_result, ARR_SIZE, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
	MPI_Reduce(numbers, sum_result, ARR_SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(numbers, prod_result, ARR_SIZE, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("\nMax reduction: ");
		for (int i = 0; i < ARR_SIZE; i++) {
			printf("%d ", max_result[i]);
		}
		printf("\n");

		printf("Min reduction: ");
		for (int i = 0; i < ARR_SIZE; i++) {
			printf("%d ", min_result[i]);
		}
		printf("\n");

		printf("Sum reduction: ");
		for (int i = 0; i < ARR_SIZE; i++) {
			printf("%d ", sum_result[i]);
		}
		printf("\n");

		printf("Prod reduction: ");
		for (int i = 0; i < ARR_SIZE; i++) {
			printf("%d ", prod_result[i]);
		}
		printf("\n\n");
	}

	MPI_Finalize();
	return 0;
}
