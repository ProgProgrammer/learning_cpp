#include "parallel.h"
#include "omp.h"

void Parallel::twoTask(const int argc, char** argv)
{
	int nError, nProvided, nRank;
	//nError = MPI_Init_thread(&argc, &argv, MPI_THREAD_SERIALIZED, &nProvided);
	//nError = MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &nProvided);
	//nError = MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &nProvided);
	nError = MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &nProvided);

	if (nError != MPI_SUCCESS)
	{
		std::cout << "Error initializing MPI" << std::endl;
		return;
	}
	MPI_Comm_rank(MPI_COMM_WORLD, &nRank);
	//if (nProvided < MPI_THREAD_SERIALIZED)
	//if (nProvided < MPI_THREAD_MULTIPLE)
	//if (nProvided < MPI_THREAD_FUNNELED)
	if (nProvided < MPI_THREAD_SINGLE)
	{
		if (nRank == 0)
			std::cout << "Serialized MPI not supportde, provided " << nProvided
			<< std::endl;
	}
	else
	{
		if (nRank == 0)
		{
			std::cout << "Success" << std::endl;
		}

#pragma omp parallel
		{
			int bMain = 0;
			char* cMain = NULL;
			char main[6] = " main";
			char n_main[10] = " not main";
			int nThread = omp_get_thread_num();
			MPI_Is_thread_main(&bMain);
			cMain = (bMain ? main : n_main);
			//std::cout << "MPI_THREAD_SERIALIZED: Process, " << nRank << " Thread " << nThread	<< cMain << std::endl;
			//std::cout << "MPI_THREAD_MULTIPLE Process, " << nRank << " Thread " << nThread	<< cMain << std::endl;
			//std::cout << "MPI_THREAD_FUNNELED Process, " << nRank << " Thread " << nThread	<< cMain << std::endl;
			std::cout << "MPI_THREAD_SINGLE Process, " << nRank << " Thread " << nThread	<< cMain << std::endl;
		}
	}

	MPI_Finalize();
}