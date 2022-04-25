#include "classes_mover_interface.h"

LineMover::LineMover(const int & c_x, const int & c_y, const int & speed) : x(c_x), y(c_y), v(speed)
{}

void LineMover::Calculate(const int & timeStamp)
{
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
    srand(time(nullptr));
    int random_variable = rand() % 10 + 1;
    x = x + random_variable * v * timeStamp;
    y = y + random_variable * v * timeStamp;
}

int RandomMover::GetX() const
{
    return x;
}

int RandomMover::GetY() const
{
    return y;
}