#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "classes_mover_interface.h"
#include "class_projectiler_mover.h"
#include "static_objects.h"
#include "create_map.h"

int main()
{
    windowStruct * winMap = new windowStruct;  // ��������� � ����������� ����
    winMap->weight = 950;
    winMap->height = 950;

    // �����:
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

    winMap->color = 4;  // ���� ���� "Blue"
    winMap->name_window ="Rendering the rectangle.";

    // ������ � ������ ��������:
    winMap->map =
    {
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 2, 2, 2, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 2, 2, 2, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 2, 2, 2, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1,
    };  

    winMap->length_window = 19;

    objectStruct stat_object, guided_tank, projectile_object;  // �������, ������� ����� �� ����� (� 1 �� 3)
    stat_object.weight = stat_object.height = stat_object.step = guided_tank.weight = guided_tank.height = 
        guided_tank.step = projectile_object.weight = projectile_object.height = 50;

    // �������� ����� � ��������:
    projectile_object.step = 1;
    stat_object.step = 50;
    guided_tank.step = 50;

    // �����:
    stat_object.color = 7;        // Cyan
    guided_tank.color = 6;        // Magenta
    projectile_object.color = 2;  // Red

    winMap->objsArray.push_back(stat_object);        // ����������� ������
    winMap->objsArray.push_back(guided_tank);        // ����������� ������ (����)
    winMap->objsArray.push_back(projectile_object);  // ������ (����� ����� ����� 3 �� �����)   

    CreateMap * cm = new CreateMap(winMap);

    sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(winMap->weight, winMap->height), winMap->name_window);
    bool crwn = false;

    while (window->isOpen())
    {
        sf::Event event;      

        if (crwn != true)
            crwn = cm->createWindow(window);

        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
    }

    delete cm;
    delete winMap;

    return 0;
}