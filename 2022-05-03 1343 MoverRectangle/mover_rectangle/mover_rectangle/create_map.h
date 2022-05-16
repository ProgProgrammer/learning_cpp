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
    std::string name_window;              // �������� ����
    std::vector<int> map;                 // ������ � ������ ��������
    std::vector<objectStruct> objsArray;  // ������ ��������
    int length_window;
};

class CreateMap
{
private:
    int & weight;
    int & height;
    std::vector<sf::Color> colors = { sf::Color::Black, sf::Color::White, sf::Color::Red, sf::Color::Green,
        sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Transparent };
    sf::Color & color;                                // ��������� ���� �� ������� "colors"
    std::string & name_window;                        // �������� ����
    std::vector<int> & map;                           // ������ � ������ ��������
    std::vector<objectStruct> & objsArray;            // ������ ��������
    windowStruct * winSct;                            // ������ ��������� "windowStruct"
    std::vector<sf::RectangleShape> renderedObjects;  // ������ �������� ��� ����������� � ����

public:
    CreateMap(windowStruct & ws);
    CreateMap(windowStruct * ws);
    bool createWindow(sf::RenderWindow * window);
    bool updateWindow();
};