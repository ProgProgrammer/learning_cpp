#include "rectangle.h"

Rectangle::Rectangle(const float x, const float y, const float width, const float height,
    const std::shared_ptr<sf::RenderWindow> window,
    const sf::Color color, const float angle_rotation)
    : FigureData(x, y, width, height, window, color, angle_rotation)
{
    m_rectangle = sf::RectangleShape(sf::Vector2f(width, height));
}

void Rectangle::draw()
{
    drawFigureTemplate(m_rectangle);
}