#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

// Цвета:
enum colors
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
    StatObj = 1,
    TankUser = 2,
    Gun = 3
};

struct ObjectStruct
{
    int weight;
    int height;
    int step;
    colors color;
};

struct MoverObject  // структура для хранения информации о передвигаемом объекте
{
    int num_fig_width;   // ширина перемещаемого объекта в подобъектах
    int num_fig_height;  // высота перемещаемого объекта в подобъектах
    int num_mover_obj;   // номер подобъектов передвигаемого объекта
    int rotated_obj;     // номер поворачиваемых подобъектов передвигаемого объекта
};

struct WindowStruct
{
    int weight;
    int height;
    int color;
    std::string name_window;              // название окна
    std::vector<int> map;                 // массив с картой объектов
    std::vector<ObjectStruct> objsArray;  // массив объектов
    int length_window;
};

class Map
{
public:
    virtual bool createWindow(sf::RenderWindow * window) = 0;
    virtual bool updateWindow() = 0;
};

class MoverInterface
{
public:
    virtual bool Calculate(sf::Event & event) = 0;
};