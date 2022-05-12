#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "class_mover_interface.h"
#include "classes_mover_interface.h"

class ProjectilerMover : public MoverInterface
{
private:
    int x;
    int y;
    int v;
    int timeStamp;
    int x_screen;
    int y_screen;
    float weight;
    float height;
    float half_weight;
    float half_height;
    sf::RenderWindow & window;
    sf::RectangleShape & projectiler;
    sf::RectangleShape & rectangle;
    bool CheckScreenY(const int & timeStamp);

public:
    ProjectilerMover(sf::RenderWindow & window, sf::RectangleShape & projectiler, sf::RectangleShape & rct,
        const int & c_x, const int & c_y, const int & timeStamp = 1, const int & speed = 1,
        const int & x_scr = 640, const int & y_scr = 480, const float & w = 10, const float & h = 10);
    virtual void CalculateXU() override {}
    virtual void CalculateXD() override {}
    virtual void CalculateYU() override;
    virtual void CalculateYD() override {}
    virtual int GetX() const override;
    virtual int GetY() const override;
};