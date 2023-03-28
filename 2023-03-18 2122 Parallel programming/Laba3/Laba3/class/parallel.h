#include "mpi.h"
#include <iostream>

class Parallel
{
private:
    void oneTask(const int argc, char** argv);
    void twoTask(const int argc, char** argv);
    void threeTask(const int argc, char** argv);
public:
    void startLoop(const int argc, char** argv)
    {
        //oneTask(argc, argv);
        //twoTask(argc, argv);
        threeTask(argc, argv);
    }
};