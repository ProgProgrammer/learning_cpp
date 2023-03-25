#include <iostream>
#include "mpi.h"
#include "class/parallel.h"

int main(const int argc, char** argv)
{
	Parallel obj;
	obj.startLoop(argc, argv);

	return 0;
}