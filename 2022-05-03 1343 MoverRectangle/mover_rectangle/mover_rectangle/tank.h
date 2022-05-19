#pragma once
#include <iostream>
#include "class_mover_interface.h"

class Tank : public MoverInterface
{
private:
    WindowStruct * map;
    MoverObject * tank;
    int middle_horizontal_top;
    int middle_horizontal_down;
    int middle_id;
    int middle_vertical_left;
    int middle_vertical_right;
    std::vector<int> nums_tank;
    std::vector<int> id_tank;
    void addedValues();

public:
    Tank(WindowStruct & map, MoverObject & tank);
    Tank(WindowStruct * map, MoverObject * tank);
    virtual bool calculate(sf::Event & event) override;
};