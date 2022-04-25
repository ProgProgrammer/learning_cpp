#pragma once
#include <iostream>
#include "class_mover_interface.h"

class LineMover : public MoverInterface
{
private:
    int x;
    int y;
    int v;

public:
    LineMover(const int & c_x = 0, const int & c_y = 0, const int & speed = 0);
    virtual void Calculate(const int & timeStamp) override;
    virtual int GetX() const override;
    virtual int GetY() const override;
};

class RandomMover : public MoverInterface
{
private:
    int x;
    int y;
    int v;
    int prevTimeStamp = 0;

public:
    RandomMover(const int & c_x = 0, const int & c_y = 0, const int & speed = 0);
    virtual void Calculate(const int & timeStamp) override;
    virtual int GetX() const override;
    virtual int GetY() const override;
};