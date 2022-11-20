#include "rectangle.h"

Rectangle::Rectangle(const float x, const float y, const float length, const std::shared_ptr<sf::RenderWindow> window, const sf::Color color, const float turning_radius)
    : m_dx(x), m_dy(y), m_figure_length(length), m_window(window), m_color(color), m_turning_radius(turning_radius)
{
    m_rectangle = sf::RectangleShape(sf::Vector2f(m_figure_length + m_figure_length, m_figure_length));
}

void Rectangle::draw()
{
    m_rectangle.setFillColor(m_color);
    m_rectangle.setPosition(m_dx, m_dy);
    m_rectangle.setOrigin(m_figure_length, m_figure_length);
    m_rectangle.setRotation(m_turning_radius);
    m_window->draw(m_rectangle);
}