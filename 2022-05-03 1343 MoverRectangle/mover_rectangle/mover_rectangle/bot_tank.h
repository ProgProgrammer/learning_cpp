#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "class_mover_interface.h"
#include "timer.h"
#include "create_map.h"
#include "tank.h"

class BotTank : public Tank
{
private:
    enum DirectionsGun
    {
        top,    // 0
        left,   // 1
        right,  // 2
        bottom  // 3
    };
    WindowStruct* map;  // карта
    MoverObject* tank;  // танк
    sf::RenderWindow* window;
    CreateMap* copy_map;
    int middle_horizontal_top;
    int middle_horizontal_down;
    int middle_id;
    int middle_vertical_left;
    int middle_vertical_right;
    int top_lines;  // половина строк сверху матрицы для вычисления высоты до начала матрицы танка
    int middle_line;  // отступ от центра танка по середине
    int gun_axis;  // идентификатор оси орудия в массиве nums_tank
    int max_pixels_map;
    bool flag_ready_to_destroy = false;
    std::vector<int> nums_tank;  // массив с информацией о строении танка
    std::vector<int> id_tank;    // массив с идентификаторами танка на карте
    Tank * main_tank;  // главный танк на карте
    std::string gun = "gun";
    int position_gun = 0;  // позиция конца орудия
    int direction_gun;
    bool moving_gun = true;  // проверка на то, было ли изменено положение орудия или нет
    bool destroyedObj(int i);  // эффект уничтожения объекта

public:
    BotTank(WindowStruct& map, MoverObject& tank, sf::RenderWindow* window, CreateMap& cm, Tank * main_tank, std::vector<BotTank*> & bot_tanks);
    virtual bool calculate(sf::Event & event) override;
};