#pragma once
#include "figure_data.h"
#include <SFML/Graphics.hpp>

class Triangle : public FigureData
{
private:
    sf::CircleShape m_triangle;  // объект "треугольник"

public:
    Triangle(const float x, const float y, const float width, const float height,
        const std::shared_ptr<sf::RenderWindow> window,
        const sf::Color color, const float angle_rotation = 0);
    void draw() override;
};