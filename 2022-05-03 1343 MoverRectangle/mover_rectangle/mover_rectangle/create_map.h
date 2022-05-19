#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "class_mover_interface.h"

class CreateMap : public Map
{
private:
    int & weight;
    int & height;
    std::vector<sf::Color> colors = { sf::Color::Black, sf::Color::White, sf::Color::Red, sf::Color::Green,
        sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Transparent };
    sf::Color & color;                                // выбранный цвет из массива "colors"
    std::string & name_window;                        // название окна
    std::vector<int> & map;                           // массив с картой объектов
    std::vector<ObjectStruct> & objsArray;            // массив объектов
    WindowStruct * winSct;                            // объект структуры "WindowStruct"
    std::vector<sf::RectangleShape> renderedObjects;  // массив объектов для отображения в окне

public:
    CreateMap(WindowStruct & ws);
    CreateMap(WindowStruct * ws);
    virtual bool createWindow(sf::RenderWindow * window) override;
};