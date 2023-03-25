#include <iostream>
#include "mpi.h"
#include "class/parallel.h"

int main(int argc, char** argv)
{
	Parallel obj;
	obj.startLoop(argc, argv);

	return 0;
}