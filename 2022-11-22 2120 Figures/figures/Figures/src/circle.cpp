#include "circle.h"

Circle::Circle(const float x, const float y, const float length, const std::shared_ptr<sf::RenderWindow> window, const sf::Color color, const float turning_radius)
    : m_dx(x), m_dy(y), m_figure_length(length), m_window(window), m_color(color), m_turning_radius(turning_radius)
{
    m_circle = sf::CircleShape(m_figure_length);
}

void Circle::draw()
{
    m_circle.setFillColor(m_color);
    m_circle.setPosition(m_dx, m_dy);
    m_circle.setOrigin(m_figure_length, m_figure_length);
    m_circle.setRotation(m_turning_radius);
    m_window->draw(m_circle);
}