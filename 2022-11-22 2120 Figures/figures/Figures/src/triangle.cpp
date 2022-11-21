#include "triangle.h"
#include <iostream>

Triangle::Triangle(const float x, const float y, const float width, const float height,
    const std::shared_ptr<sf::RenderWindow> window,
    const sf::Color color, const float angle_rotation)
    : FigureData(x, y, width, height, window, color, angle_rotation)
{
    m_triangle = sf::CircleShape(width, 3);
}

void Triangle::draw()
{
    drawFigureTemplate(m_triangle);
}