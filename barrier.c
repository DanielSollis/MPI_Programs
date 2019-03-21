#include <mpi.h>
#include <stdio.h>
#include <time.h>

int local_computation();

int main(int argc, char * argv[])
{
	double start, end, total;
	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	srand(time(NULL) * (rank + 1));
	start = MPI_Wtime();
	int rand_num = local_computation();
	MPI_Barrier(MPI_COMM_WORLD);	//have all processes synchronize
	end = MPI_Wtime();
	total = end - start;
	printf("num %d total: %f\n", rand_num, total);
	MPI_Finalize();
	return 0;
}


int local_computation() {
	int rand_num = rand() % 10000;
	for (int i = 0; i < rand_num; i++) {
		for (int j = 0; j < rand_num; j++) {
			int x = i + rand_num;
			int y = x % rand_num + i;
		}
	}
	return rand_num;
}