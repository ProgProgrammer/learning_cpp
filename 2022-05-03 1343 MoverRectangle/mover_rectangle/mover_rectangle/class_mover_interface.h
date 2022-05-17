#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

struct objectStruct
{
    int weight;
    int height;
    int step;
    int color;
};

struct moverObject  // структура для хранения информации о передвигаемом объекте
{
    int num_fig_width;   // ширина перемещаемого объекта в подобъектах
    int num_fig_height;  // высота перемещаемого объекта в подобъектах
    int num_mover_obj;   // номер подобъектов передвигаемого объекта
    int rotated_obj;     // номер поворачиваемых подобъектов передвигаемого объекта
};

struct windowStruct
{
    int weight;
    int height;
    int color;
    std::string name_window;              // название окна
    std::vector<int> map;                 // массив с картой объектов
    std::vector<objectStruct> objsArray;  // массив объектов
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
    virtual bool CalculateXU() = 0;
    virtual bool CalculateXD() = 0;
    virtual bool CalculateYL() = 0;
    virtual bool CalculateYR() = 0;
};