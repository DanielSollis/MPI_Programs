#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	MPI_Init(&argc, &argv);
	MPI_Group group_world, odd_group, even_group;
	int size, rank, num_even, num_odd, members[8], nonmembers[8], ierr;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	//gives the group handle of a specific group
	MPI_Comm_group(MPI_COMM_WORLD, &group_world);
	num_even = (size + 1)/2;
	num_odd = size - num_even;

	for (int i = 0; i < num_even; i++) {
		members[i] = i * 2;
		nonmembers[i] = members[i];
	}

	//includes ranks of the rank given in members, uses the rank from group world 
	MPI_Group_incl(group_world, num_even, members, &even_group);
	//excludes non members
	MPI_Group_excl(group_world, num_even, nonmembers, &odd_group);

	//MPI_Group_rank gives the rank of the process within the specified group
	int even_rank, odd_rank;
	MPI_Group_rank(MPI_Group even_group, &odd_rank);
	MPI_Group_rank(MPI_Group even_group, &even_rank);

	//MPI_Comm_create takes a Comms group and creates a new comm out of it
	MPI_Comm even_comm;
	MPI_Comm_create(MPI_COMM_WORLD, even_group, &even_comm);

	//group free returns a group to the system when it is no longer needed
	MPI_Group_free(even_group)

	MPI_Finalize();
	return 0;
}
