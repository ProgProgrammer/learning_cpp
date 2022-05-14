#pragma once

struct projMov
{
    int w_projectiler;
    int h_projectiler;
    int x_projectiler;
    int y_projectiler;
    int speed_projectiler;
};

struct recMov
{
    int weight_screen;
    int height_screen;
    int weight_rectangle;
    int height_rectangle;
    int x;
    int y;
    int speed;
    int timeStamp;
};

class MoverInterface
{
public:
    virtual void CalculateXU() = 0;
    virtual void CalculateXD() = 0;
    virtual void CalculateYU() = 0;
    virtual void CalculateYD() = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
};