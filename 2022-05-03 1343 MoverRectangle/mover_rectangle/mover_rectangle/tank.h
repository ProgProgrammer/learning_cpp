#pragma once
#include <iostream>
#include "class_mover_interface.h"

class Tank : public MoverInterface
{
private:
    windowStruct * map;
    moverObject * tank;
    int middle_horizontal_top;
    int middle_horizontal_down;
    int middle_id;
    int middle_vertical_left;
    int middle_vertical_right;
    std::vector<int> nums_tank;
    std::vector<int> id_tank;
    void addedValues();

public:
    Tank(windowStruct & map, moverObject & tank);
    Tank(windowStruct * map, moverObject * tank);
    virtual bool CalculateXU() override;
    virtual bool CalculateXD() override;
    virtual bool CalculateYL() override;
    virtual bool CalculateYR() override;
};