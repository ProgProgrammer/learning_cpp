#include "square.h"
#include <iostream>

Square::Square(const float x, const float y, const float width, const float height,
    const std::shared_ptr<sf::RenderWindow> window,
    const sf::Color color, const float angle_rotation)
    : FigureData(x, y, width, height, window, color, angle_rotation)
{
    m_square = sf::CircleShape(width, 4);
}

void Square::draw()
{
    drawFigureTemplate(m_square);
}