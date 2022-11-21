#pragma once
#include "figure_data.h"
#include <SFML/Graphics.hpp>

class Rectangle : public FigureData
{
private:
    sf::RectangleShape m_rectangle;

public:
    Rectangle(const float x, const float y, const float width, const float height,
        const std::shared_ptr<sf::RenderWindow> window,
        const sf::Color color, const float angle_rotation = 0);
    void draw() override;
};