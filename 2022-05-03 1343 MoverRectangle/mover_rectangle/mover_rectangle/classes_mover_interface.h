#pragma once
#include <iostream>
#include "class_mover_interface.h"

class RectangleMover : public MoverInterface
{
private:
    int x;
    int y;
    int v;
    int timeStamp;
    int x_screen;
    int y_screen;
    int weight;
    int height;
    int half_weight;
    int half_height;
    bool CheckScreenX(const int & timeStamp);
    bool CheckScreenY(const int & timeStamp);

public:
    RectangleMover(const recMov & rm);
    virtual void CalculateXU() override;
    virtual void CalculateXD() override;
    virtual void CalculateYU() override;
    virtual void CalculateYD() override;
    virtual int GetX() const override;
    virtual int GetY() const override;
};