#pragma once
#include <iostream>
#include "class_mover_interface.h"

class Tank : public MoverInterface
{
private:
    WindowStruct * map;  // карта
    MoverObject * tank;  // танк
    int middle_horizontal_top;
    int middle_horizontal_down;
    int middle_id;
    int middle_vertical_left;
    int middle_vertical_right;
    int top_lines;  // половина строк сверху матрицы для вычисления высоты до начала матрицы танка
    int middle_line;  // отступ от центра танка по середине
    int gun_axis;  // идентификатор оси орудия в массиве nums_tank
    int max_pixels_map;
    std::vector<int> nums_tank;  // массив с информацией о строении танка
    std::vector<int> id_tank;    // массив с идентификаторами танка на карте
    std::string gun = "gun";
    int position_gun = 0;  // позиция конца орудия
    std::string direction_gun;
    bool moving_gun = true;  // проверка на то, было ли изменено положение орудия или нет
    bool tankDrawing(std::string obj = "");  // отрисовка танка
    bool removeGun();

public:
    Tank() {}  // создание пустого объекта для того, чтобы создать проверку танка на соприкосновение с объектами и выходом за границу при первоначальной отрисовке
    Tank(WindowStruct & map, MoverObject & tank);
    virtual bool calculate(sf::Event & event) override;
};