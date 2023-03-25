#include "mpi.h"

class Parallel
{
private:
    void oneTask(int argc, char** argv);
public:
    void startLoop(int argc, char** argv)
    {
        oneTask(argc, argv);
    }
};