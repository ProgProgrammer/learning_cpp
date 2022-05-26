#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

// Цвета:
enum Colors
{
    Black,       // 0
    White,       // 1
    Red,         // 2
    Green,       // 3
    Blue,        // 4
    Yellow,      // 5
    Magenta,     // 6
    Cyan,        // 7
    Transparent  // 8
};

// Номера объектов на карте:
enum Objects
{
    EmptyObject = 0,
    StatObj = 1,
    TankUser = 2,
    Gun = 3,
    Projectile = 4,
    DestroyedObj = 5
};

struct ObjectStruct
{
    int weight;
    int height;
    int step;
    Colors color;
};

struct MoverObject  // структура для хранения информации о передвигаемом объекте
{
    int num_fig_width;   // ширина перемещаемого объекта в подобъектах
    int num_fig_height;  // высота перемещаемого объекта в подобъектах
    int num_mover_obj;   // номер подобъектов передвигаемого объекта
    int rotated_obj;     // номер поворачиваемых подобъектов передвигаемого объекта
    int projectile_obj;  // номер снаряда
    int destroyed_obj;   // номер уничтоженного объекта
    int center_obj;      // центр перемещаемого объекта
};

struct WindowStruct
{
    int weight;
    int height;
    int color;
    std::string name_window;              // название окна
    std::vector<int> map;                 // массив с картой объектов
    std::vector<ObjectStruct> objsArray;  // массив объектов
    int width_window;
    int height_window;
};

class Map
{
public:
    virtual bool updateWindow(sf::RenderWindow * window) = 0;
};

class MoverInterface
{
public:
    virtual bool calculate(sf::Event & event) = 0;
    virtual std::vector<int> returnIdTank() const = 0;
};