#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "tank.h"
#include "bot_tank.h"
#include "create_map.h"

int main()
{
    WindowStruct winMap;  // структура с параметрами окна
    winMap.weight = 950;
    winMap.height = 950;

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
    TankUser, // 2
    Gun       // 3
    */

    winMap.color = Blue;  // цвет окна "Blue"
    winMap.name_window = "Tanks";

    // Массив с картой объектов:
    winMap.map =
    {
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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

    winMap.width_window = 19;
    winMap.height_window = 19;

    // Объекты, которые будут на карте (ширина, высота, величина шагов в пикселях и цвет объектов):
    ObjectStruct stat_object = { 50, 50, 50, Cyan };        // цвет статических объектов - Cyan
    ObjectStruct guided_tank = { 50, 50, 50, Magenta };     // цвет танка - Magenta
    ObjectStruct gun = { 50, 50, 50, Green };               // цвет орудия танка - Green
    ObjectStruct projectile_object = { 50, 50, 50, Red };    // цвет снаряда - Red
    ObjectStruct affected_object = { 50, 50, 50, Yellow };   // цвет пораженного объекта - Yellow

    winMap.objsArray.push_back(stat_object);        // статический объект
    winMap.objsArray.push_back(guided_tank);        // управляемый объект (танк)  
    winMap.objsArray.push_back(gun);                // орудие   
    winMap.objsArray.push_back(projectile_object);  // снаряд (будет равен числу 3 на карте)
    winMap.objsArray.push_back(affected_object);    // пораженный объект (будет равен числу 4 на карте)

    //Пропорции танка должны быть нечетными и одинаковыми по размеру
    MoverObject tank_struct;  // танк
    tank_struct.num_fig_width = 3;   // ширина объекта в подобъектах
    tank_struct.num_fig_height = 3;  // высота объекта в подобъектах
    tank_struct.num_mover_obj = TankUser;     // номер подобъектов танка
    tank_struct.rotated_obj = Gun;            // номер поворачиваемых подобъектов танка
    tank_struct.projectile_obj = Projectile;  // номер снаряда
    tank_struct.destroyed_obj = DestroyedObj; // номер уничтоженного объекта
    tank_struct.center_obj = 142;             // номер поворачиваемых подобъектов танка

    //Пропорции танка-бота должны быть нечетными и одинаковыми по размеру
    MoverObject bot_tank_struct;  // бот-танк
    bot_tank_struct.num_fig_width = 3;   // ширина объекта в подобъектах
    bot_tank_struct.num_fig_height = 3;  // высота объекта в подобъектах
    bot_tank_struct.num_mover_obj = TankUser;     // номер подобъектов танка
    bot_tank_struct.rotated_obj = Gun;            // номер поворачиваемых подобъектов танка
    bot_tank_struct.projectile_obj = Projectile;  // номер снаряда
    bot_tank_struct.destroyed_obj = DestroyedObj; // номер уничтоженного объекта
    bot_tank_struct.center_obj = 24;             // номер поворачиваемых подобъектов танка

    //Пропорции танка-бота должны быть нечетными и одинаковыми по размеру
    MoverObject bot_tank_struct2;  // бот-танк
    bot_tank_struct2.num_fig_width = 3;   // ширина объекта в подобъектах
    bot_tank_struct2.num_fig_height = 3;  // высота объекта в подобъектах
    bot_tank_struct2.num_mover_obj = TankUser;     // номер подобъектов танка
    bot_tank_struct2.rotated_obj = Gun;            // номер поворачиваемых подобъектов танка
    bot_tank_struct2.projectile_obj = Projectile;  // номер снаряда
    bot_tank_struct2.destroyed_obj = DestroyedObj; // номер уничтоженного объекта
    bot_tank_struct2.center_obj = 212;             // номер поворачиваемых подобъектов танка

    CreateMap cm(winMap);

    sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(winMap.weight, winMap.height), winMap.name_window);
    std::vector<BotTank*> tanks;
    Tank tank(winMap, tank_struct, window, cm, tanks);
    BotTank botTank(winMap, bot_tank_struct, window, cm, &tank, tanks);
    BotTank botTank2(winMap, bot_tank_struct2, window, cm, &tank, tanks);
    tanks.push_back(&botTank);
    tanks.push_back(&botTank2);

    /*try
    {
        tank;   // если вызвано исключение, то перейти к catch
    }
    catch (std::runtime_error & error)
    {
        std::cout << std::endl << "Tank: " << error.what() << std::endl;  // вывод исключения в консоль
    }

    try
    {
        botTank;   // если вызвано исключение, то перейти к catch
    }
    catch (std::runtime_error& error)
    {
        std::cout << std::endl << "Bot tank: " << error.what() << std::endl;  // вывод исключения в консоль
    }*/

    while (window->isOpen())
    {
        sf::Event event;
        window->pollEvent(event);

        if (!tank.isReadyToDestroy())
            tank.calculate(event);

        int i = 0;

        while (i < tanks.size())
        {
            if (!tanks[i]->isReadyToDestroy())
            {
                tanks[i]->calculate(event);
                i++;
            }
            else
                tanks.erase(tanks.begin() + i);
        }

        static int counter = 0;
        std::cout << counter++ << std::endl;

        cm.updateWindow(window);

        if (event.type == sf::Event::Closed)
            window->close();

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1000ms / 24);  // обновление экрана (заход на следующий цикл) в секунду FPS
    }

    delete window;

    return 0;
}