#include <iostream>
#include <string>

const int BUF = 512;
const int N = 5;
char buffer[BUF];

template<class T>
void inPut(T* p1, T* p2, float num)
{
	for (int i = 0; i < N; i++)
	{
		p2[i] = p1[i] = 1000 + num * i;
	}
}

template<class T>
void outPut(T* p1, T* p2)
{
	for (int i = 0; i < N; i++)
	{
		std::cout << p1[i] << " at " << &p1[i] << "; ";
		std::cout << p2[i] << " at " << &p2[i] << std::endl;
	}
}

int main()
{
	double* pd1, * pd2;
	int i;

	std::cout << "Calling new and placement new:" << std::endl;
	pd1 = new double[N];
	pd2 = new (buffer) double[N];

	for (int i = 0; i < N; i++)
	{
		pd2[i] = pd1[i] = 1000 + 20.0 * i;
	}

	inPut(pd1, pd2, 20.0);

	std::cout << "Memory addresses:" << std::endl << "heap: " << pd1 << " static: " << &buffer << std::endl;
	std::cout << "Memory contents:" << std::endl;

	outPut(pd1, pd2);

	std::cout << std::endl << "Calling new and placement new a second time:" << std::endl;

	decltype(pd1) pd3, pd4;
	pd3 = new double[N];
	pd4 = new (buffer) double[N];

	inPut(pd3, pd4, 40.0);

	std::cout << "Memory contents:" << std::endl;

	outPut(pd3, pd4);

	std::cout << std::endl << "Calling new and placement new a third time:" << std::endl;

	delete[] pd1;

	pd1 = new double[N];
	pd2 = new (buffer + N * sizeof(buffer)) double[N];

	inPut(pd1, pd2, 60.0);

	std::cout << "Memory contents:" << std::endl;

	outPut(pd1, pd2);

	delete[] pd1;
	delete[] pd3;

	std::string str = "";

	for (int i = 0; i < BUF; i++)
	{

		str += buffer[i];

		std::cout << double(buffer[i]);

		if ((i + 1) % sizeof(double) == 0)
		{
			std::cout << " = " << str << std::endl;

			str = "";
		}
	}
}