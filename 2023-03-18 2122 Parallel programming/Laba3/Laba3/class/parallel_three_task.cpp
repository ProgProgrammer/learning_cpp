#include "parallel.h"

void Parallel::threeTask(const int argc, char** argv)
{
	int nSize, nRank;
	int N;
	double start = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &nRank);
	if (nRank == 0)
	{
		// ������ N
		std::cout << "N = ";
		std::cin >> N;
		start = MPI_Wtime();
		// ��������� N �� ���������
		for (int i = 1; i < nSize; i++)
		{
			MPI_Send(&N, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			++N;
		}

		//MPI_Send(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	
	if (nRank > 0)
	{
		for (int i = 1; i < nSize; ++i)
		{
			MPI_Status pStatus;
			MPI_Recv(&N, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &pStatus);
			std::cout << "nRank = " << nRank << ". " << "N = " << N << std::endl;
		}
		//������� ���������
		std::cout << "Time is " << MPI_Wtime() - start << std::endl;
	}

	MPI_Finalize();

	/*int nSize, nRank;
	int N;
	double start, s = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &nRank);
	if (nRank == 0)
	{
		// ������ N
		std::cout << "N = ";
		std::cin >> N;
		start = MPI_Wtime();
		// ��������� N �� ���������
		for (int i = 1; i < nSize; i++)
			MPI_Send(&N, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
	}
	else
	{
		// ��� �������� N �� 0 ��������
		MPI_Status pStatus;
		MPI_Recv(&N, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &pStatus);
	}
	// ������� ���� ������
	int N_loc = N / nSize;
	for (int i = nRank * N_loc; i < (nRank + 1) * N_loc; i++)
		s += sin(i) * cos(i) * tan(i);
	// ����� ��� ��������� ���� ������
	if (nRank == 0)
	{
		double s_local;
		MPI_Status pStatus;
		// ���������� � ����� N ���������� ��������� N �� ���������
		for (int i = 1; i < nSize; i++)
		{
			// ��������
			MPI_Recv(&s_local, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &pStatus);
			// ����������
			s += s_local;
		}
		//������� ���������
		std::cout << "S = " << s << ". Time is " << MPI_Wtime() - start << std::endl;
	}
	else
		// ���� ������� �� �������, �� �������� ��� ���� ��������� �����
		MPI_Send(&s, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	MPI_Finalize();*/
}