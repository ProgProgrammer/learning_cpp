#include "classes_mover_interface.h"

RectangleMover::RectangleMover(const int & c_x, const int & c_y, const int & speed,
    const int & x_scr, const int & y_scr, const int & w, const int & h)
    : x(c_x), y(c_y), v(speed), x_screen(x_scr), y_screen(y_scr), weight(w), height(h)
{
    half_weight = weight / 2;
    half_height = height / 2;

    if (x - half_weight < 0 || x + half_weight > x_screen)
        throw std::logic_error("wrong coordinate 'x'");

    if (y - half_height < 0 || y + half_height > y_screen)
        throw std::logic_error("wrong coordinate 'y'");
}

bool RectangleMover::CheckScreen(const int & timeStamp, const std::string & str)
{
    int num;

    if (str == "x")
    {
        num = x + v * timeStamp;

        if (num - half_weight < 0 || num + half_weight > x_screen)
            return false;
    }
    else if (str == "y")
    {
        num = y + v * timeStamp;

        if (num - half_height < 0 || num + half_height > y_screen)
            return false;
    }

    return true;
}

void RectangleMover::Calculate(const int & timeStamp, const std::string & str)
{
    if (timeStamp != 0 && str == "x" && CheckScreen(timeStamp, str))
    {
        x = x + v * timeStamp;
        std::cout << "X = " << x << std::endl;
    }
    else if (timeStamp != 0 && str == "y" && CheckScreen(timeStamp, str))
    {
        y = y + v * timeStamp;
        std::cout << "Y = " << y << std::endl;
    }
    else if (str != "x" && str != "y")
        throw std::logic_error("no such side");
}

int RectangleMover::GetX() const
{
    return x;
}

int RectangleMover::GetY() const
{
    return y;
}