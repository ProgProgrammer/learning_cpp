#include "classes_mover_interface.h"

LineMover::LineMover(const int & c_x, const int & c_y, const int & speed) : x(c_x), y(c_y), v(speed)
{}

void LineMover::Calculate(const int & timeStamp)
{
    if (timeStamp < 0)
        throw std::logic_error("timestep < 0");
    
    x = x + v * timeStamp;
}

int LineMover::GetX() const
{
    return x;
}

int LineMover::GetY() const
{
    return y;
}

RandomMover::RandomMover(const int & c_x, const int & c_y, const int & speed) : x(c_x), y(c_y), v(speed)
{}

void RandomMover::Calculate(const int & timeStamp)
{
    if (timeStamp < 0)
        throw std::logic_error("timestep < 0");

    srand(time(nullptr));
    int timeDiff = timeStamp - prevTimeStamp;
    x = x + rand() * v * timeDiff;
    x = y + rand() * v * timeDiff;
    prevTimeStamp = timeStamp;
}

int RandomMover::GetX() const
{
    return x;
}

int RandomMover::GetY() const
{
    return y;
}