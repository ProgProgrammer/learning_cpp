#include <iostream>

namespace Jack  // ������������ ���� Jack
{
	int pal;
	double pail;

	void fetch()
	{
		std::cout << pal << std::endl;   // 15
		std::cout << pail << std::endl;  // 15.5
	}
}

int main()
{
	Jack::pal = 15;
	Jack::pail = 15.05;

	Jack::fetch();

	std::cout << Jack::fetch;  // ������� ����� ������� � �����?
}