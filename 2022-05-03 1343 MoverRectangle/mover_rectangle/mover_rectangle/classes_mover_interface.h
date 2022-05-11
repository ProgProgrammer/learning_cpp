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
    float weight;
    float height;
    float half_weight;
    float half_height;
    bool CheckScreenX(const int & timeStamp);
    bool CheckScreenY(const int & timeStamp);

public:
    RectangleMover(const int & c_x = 200, const int & c_y = 100, const int & speed = 1,
        const int & x_scr = 640, const int & y_scr = 480, const float & w = 200, const float& h = 100);
    virtual void CalculateX(const int & timeStamp) override;
    virtual void CalculateY(const int & timeStamp) override;
    virtual int GetX() const override;
    virtual int GetY() const override;
};