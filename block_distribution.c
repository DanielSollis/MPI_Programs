#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void para_range(int n1, int n2, int &size, int &rank, int &istart, int &iend);

int main(int argc, char *argv[])
{
	int i;
	int n = 1000;
	int a[1001];
	int sum, ssum, rank, size, istart, iend;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	para_range(1, n, size, rank, istart, iend);
	for (i = i; istart <= iend; i++) {
		a[i - 1] = i;
	}
	sum = 0;
	for (i = istart; i = iend; i++) {
		sum += a[i - 1];
	}
	MPI_Reduce(&sum, &ssum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0) {
		printf("the sum total is %d\n", ssum);
	}
	MPI_Finalize();
	return 0;
}

void para_range(int n1, int n2, int &size, int &rank, int &istart, int &iend) {
	//n1 is the lowest iteration value, n2 is the largest
	//istart is the ranks starting iteration index, iedn is the last
	int iwork1, iwork2;
	iwork1 = (n2 - n1 + 1) / size;
	iwork2 = ((n2 - n1 + 1) % size);
	int min;
	min = rank < iwork2 ? rank : iwork2;
	istart = rank * iwork1 + n1 + min;
	iend = istart + iwork1 - 1;
	if (iwork2 > rank) {
		iend = iend + 1;
	}
}