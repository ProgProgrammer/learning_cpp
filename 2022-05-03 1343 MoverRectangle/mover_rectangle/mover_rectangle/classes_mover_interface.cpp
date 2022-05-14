#include "classes_mover_interface.h"

RectangleMover::RectangleMover(const recMov & rm)
    : x(rm.x), y(rm.y), v(rm.speed), timeStamp(rm.timeStamp), x_screen(rm.weight_screen), y_screen(rm.height_screen), 
    weight(rm.weight_rectangle), height(rm.height_rectangle)
{
    half_weight = weight / 2;
    half_height = height / 2;

    if (x - half_weight < 0 || x + half_weight > x_screen)
        throw std::logic_error("wrong coordinate 'x'");

    if (y - half_height < 0 || y + half_height > y_screen)
        throw std::logic_error("wrong coordinate 'y'");
}

bool RectangleMover::CheckScreenX(const int & timeStamp)
{
    int num = x + v * timeStamp;

    if (num - half_weight < 0 || num + half_weight > x_screen)
        return false;

    return true;
}

bool RectangleMover::CheckScreenY(const int & timeStamp)
{
    int num = y + v * timeStamp;

    if (num - half_height < 0 || num + half_height > y_screen)
        return false;

    return true;
}

void RectangleMover::CalculateXU()
{
    if (timeStamp != 0 && CheckScreenX(-timeStamp))
    {
        x = x + v * (-timeStamp);
        std::cout << "X = " << x << std::endl;
    }
}

void RectangleMover::CalculateXD()
{
    if (timeStamp != 0 && CheckScreenX(timeStamp))
    {
        x = x + v * timeStamp;
        std::cout << "X = " << x << std::endl;
    }
}

void RectangleMover::CalculateYU()
{
    if (timeStamp != 0 && CheckScreenY(-timeStamp))
    {
        y = y + v * (-timeStamp);
        std::cout << "Y = " << y << std::endl;
    }
}

void RectangleMover::CalculateYD()
{
    if (timeStamp != 0 && CheckScreenY(timeStamp))
    {
        y = y + v * timeStamp;
        std::cout << "Y = " << y << std::endl;
    }
}

int RectangleMover::GetX() const
{
    return x;
}

int RectangleMover::GetY() const
{
    return y;
}