#include "parallel.h"

void Parallel::oneTask(const int argc, char** argv)
{
	int rank, size;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Finalize();

	printf("Process: %d, size: %d\n", rank, size);
}