#pragma once
#include <iostream>
#include "class_mover_interface.h"

class RectangleMover : public MoverInterface
{
private:
    int x;
    int y;
    int v;
    int x_screen;
    int y_screen;
    int weight;
    int height;
    int half_weight;
    int half_height;
    bool CheckScreen(const int & timeStamp, const std::string & str);

public:
    RectangleMover(const int & c_x = 200, const int & c_y = 100, const int & speed = 1,
        const int & x_scr = 640, const int & y_scr = 480, const int & w = 200, const int & h = 100);
    virtual void Calculate(const int & timeStamp, const std::string & str) override;
    virtual int GetX() const override;
    virtual int GetY() const override;
};