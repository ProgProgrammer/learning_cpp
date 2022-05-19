#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "class_projectiler_mover.h"
#include "tank.h"
#include "static_objects.h"
#include "create_map.h"

int main()
{
    WindowStruct* winMap = new WindowStruct;  // структура с параметрами окна
    winMap->weight = 950;
    winMap->height = 950;

    // Цвета:
    /*
    Black;       // 0
    White;       // 1
    Red;         // 2
    Green;       // 3
    Blue;        // 4
    Yellow;      // 5
    Magenta;     // 6
    Cyan;        // 7
    Transparent; // 8
    */

    // Номера объектов на карте:
    /*
    StatObj,  // 1
    TankUser,     // 2
    Gun       // 3
    */

    winMap->color = Blue;  // цвет окна "Blue"
    winMap->name_window = "Tanks";

    // Массив с картой объектов:
    winMap->map =
    {
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1,
    };

    winMap->length_window = 19;

    // Объекты, которые будут на карте (ширина, высота, величина шагов в пикселях и цвет объектов):
    ObjectStruct stat_object = { 50, 50, 50, Cyan };        // цвет статических объектов - Cyan
    ObjectStruct guided_tank = { 50, 50, 50, Magenta };     // цвет танка - Magenta
    ObjectStruct projectile_object = { 50, 50, 1, Red };    // цвет орудия танка - Red
    ObjectStruct gun = { 50, 50, 50, Green };               // цвет снаряда - Green

    winMap->objsArray.push_back(stat_object);        // статический объект
    winMap->objsArray.push_back(guided_tank);        // управляемый объект (танк)  
    winMap->objsArray.push_back(gun);                // орудие   
    winMap->objsArray.push_back(projectile_object);  // снаряд (будет равен числу 3 на карте)

    MoverObject * tank_struct = new MoverObject;  // танк
    tank_struct->num_fig_width = 3;   // ширина объекта в подобъектах
    tank_struct->num_fig_height = 3;  // высота объекта в подобъектах
    tank_struct->num_mover_obj = TankUser;   // номер подобъектов танка
    tank_struct->rotated_obj = Gun;     // номер поворачиваемых подобъектов танка

    CreateMap * cm = new CreateMap(winMap);

    sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(winMap->weight, winMap->height), winMap->name_window);
    Tank * tank = new Tank(winMap, tank_struct);
    bool crwn = false;

    while (window->isOpen())
    {
        sf::Event event;

        if (crwn != true)
            crwn = cm->createWindow(window);

        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                crwn = tank->Calculate(event);

                if (crwn == true)
                {
                    crwn = cm->createWindow(window);
                    crwn = false;
                }
            }

            if (event.type == sf::Event::Closed)
                window->close();
        }
    }

    delete cm;
    delete winMap;
    delete tank;
    delete window;

    return 0;
}