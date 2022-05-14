#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "class_mover_interface.h"
#include "static_objects.h"

class ProjectilerMover : public MoverInterface
{
private:
    int x;
    int y;
    int v;
    int timeStamp;
    int x_screen;
    int y_screen;
    int weight;
    int height;
    int half_weight;
    int half_height;
    int begin_x;
    int end_x;
    int begin_y;
    int end_y;
    sf::RenderWindow & window;
    sf::RectangleShape & projectiler;
    sf::RectangleShape & rectangle;
    std::vector<StaticObjects> & stat_objs;
    std::vector<sf::RectangleShape> & rs_objs;
    bool CheckScreenY(const int & timeStamp) const;
    bool checkDestroyed();

public:
    ProjectilerMover(sf::RenderWindow & wd, sf::RectangleShape & prj, sf::RectangleShape & rct, std::vector<StaticObjects> & st_obs,
        std::vector<sf::RectangleShape> & rs_objs, const projMov & pm, const recMov & rm);
    virtual void CalculateXU() override {}
    virtual void CalculateXD() override {}
    virtual void CalculateYU() override;
    virtual void CalculateYD() override {}
    virtual int GetX() const override;
    virtual int GetY() const override;
};