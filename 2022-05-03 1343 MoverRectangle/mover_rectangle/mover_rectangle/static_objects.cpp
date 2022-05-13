#include "static_objects.h"

StaticObjects::StaticObjects(int w, int h, int x_, int y_) : weight(w), height(h), x(x_), y(y_) 
{
    begin_x = x - weight / 2;
    end_x = x + weight / 2;
    begin_y = y - height / 2;
    end_y = y + height / 2;
}

int StaticObjects::GetX() const
{
    return x;
}

int StaticObjects::GetY() const
{
    return y;
}

int StaticObjects::GetW() const
{
    return weight;
}

int StaticObjects::GetH() const
{
    return height;
}

int StaticObjects::GetBX() const
{
    return begin_x;
}

int StaticObjects::GetBY() const
{
    return begin_y;
}

int StaticObjects::GetEX() const
{
    return end_x;
}

int StaticObjects::GetEY() const
{
    return end_y;
}