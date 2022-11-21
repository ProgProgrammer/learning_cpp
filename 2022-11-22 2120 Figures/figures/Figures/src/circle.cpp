#include "circle.h"

Circle::Circle(const float x, const float y, const float width, const float height,
    const std::shared_ptr<sf::RenderWindow> window,
    const sf::Color color, const float angle_rotation)
    : FigureData(x, y, width, height, window, color, angle_rotation)
{
    m_circle  = sf::CircleShape(width);
}

void Circle::draw()
{
    drawFigureTemplate(m_circle);
}