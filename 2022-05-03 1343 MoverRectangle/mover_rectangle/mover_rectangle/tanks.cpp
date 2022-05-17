#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "class_projectiler_mover.h"
#include "tank.h"
#include "static_objects.h"
#include "create_map.h"

int main()
{
    windowStruct * winMap = new windowStruct;  // структура с параметрами окна
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

    winMap->color = 4;  // цвет окна "Blue"
    winMap->name_window ="Tanks";

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

    objectStruct stat_object, guided_tank, projectile_object, gun;  // объекты, которые будут на карте (с 1 по 3)
    stat_object.weight = stat_object.height = stat_object.step = guided_tank.weight = guided_tank.height = 
        guided_tank.step = projectile_object.weight = projectile_object.height = gun.weight = 
        gun.height = gun.step = 50;

    // Величина шагов в пикселях:
    projectile_object.step = 1;

    // Цвета:
    stat_object.color = 7;        // цвет статических объектов - Cyan
    guided_tank.color = 6;        // цвет танка - Magenta
    gun.color = 3;                // цвет орудия танка - Green
    projectile_object.color = 2;  // цвет снаряда - Red

    winMap->objsArray.push_back(stat_object);        // статический объект
    winMap->objsArray.push_back(guided_tank);        // управляемый объект (танк)  
    winMap->objsArray.push_back(gun);                // орудие   
    winMap->objsArray.push_back(projectile_object);  // снаряд (будет равен числу 3 на карте)

    moverObject * tank_struct = new moverObject;  // танк
    tank_struct->num_fig_width = tank_struct->num_fig_height = 3;  // ширина и высота объекта в подобъектах
    tank_struct->num_mover_obj = 2;  // номер подобъектов танка
    tank_struct->rotated_obj = 3;    // номер поворачиваемых подобъектов танка

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
                if (event.key.code == sf::Keyboard::W)
                {
                    crwn = tank->CalculateXU();

                    if (crwn == true)
                        crwn = cm->createWindow(window);
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    crwn = tank->CalculateXD();

                    if (crwn == true)
                        crwn = cm->createWindow(window);
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    crwn = tank->CalculateYL();

                    if (crwn == true)
                        crwn = cm->createWindow(window);
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    crwn = tank->CalculateYR();

                    if (crwn == true)
                        crwn = cm->createWindow(window);
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