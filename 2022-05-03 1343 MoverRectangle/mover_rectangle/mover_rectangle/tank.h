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
    int max_pixels_map;
    std::vector<int> nums_tank;  // массив с информацией о строении танка
    std::vector<int> id_tank;    // массив с идентификаторами танка на карте
    bool checkMap() const;  // проверка танка на соприкосновение с другими объектами на карте
    void copyMap();

public:
    Tank() {}
    Tank(WindowStruct & map, MoverObject & tank);
    virtual bool calculate(sf::Event & event) override;
};