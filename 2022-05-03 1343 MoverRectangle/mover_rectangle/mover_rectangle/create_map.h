#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "class_mover_interface.h"

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

class CreateMap
{
private:
    int & weight;
    int & height;
    std::vector<sf::Color> colors = { sf::Color::Black, sf::Color::White, sf::Color::Red, sf::Color::Green,
        sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Transparent };
    sf::Color & color;                                // выбранный цвет из массива "colors"
    std::string & name_window;                        // название окна
    std::vector<int> & map;                           // массив с картой объектов
    std::vector<objectStruct> & objsArray;            // массив объектов
    windowStruct * winSct;                            // объект структуры "windowStruct"
    std::vector<sf::RectangleShape> renderedObjects;  // массив объектов для отображения в окне

public:
    CreateMap(windowStruct & ws);
    CreateMap(windowStruct * ws);
    bool createWindow(sf::RenderWindow * window);
    bool updateWindow();
};