#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "class_mover_interface.h"

class StaticObjects : public MoverInterface
{
private:
    int weight;
    int height;
    int x;
    int y;
    int begin_x;
    int end_x;
    int begin_y;
    int end_y;
public:
    StaticObjects(int w = 0, int h = 0, int x_ = 0, int y_ = 0);
    virtual void CalculateXU() override {}
    virtual void CalculateXD() override {}
    virtual void CalculateYU() override {}
    virtual void CalculateYD() override {}
    virtual int GetX() const override;
    virtual int GetY() const override;
    int GetW() const;
    int GetH() const;
    int GetBX() const;
    int GetEX() const;
    int GetBY() const;
    int GetEY() const;
};