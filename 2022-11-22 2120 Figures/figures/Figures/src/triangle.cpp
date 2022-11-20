#include "triangle.h"

Triangle::Triangle(const float x, const float y, const float length, const std::shared_ptr<sf::RenderWindow> window, const sf::Color color, const float turning_radius)
    : m_dx(x), m_dy(y), m_figure_length(length), m_window(window), m_color(color), m_turning_radius(turning_radius)
{
    m_triangle = sf::CircleShape(m_figure_length, 3);
}

void Triangle::draw()
{
    m_triangle.setFillColor(m_color);
    m_triangle.setPosition(m_dx, m_dy);
    m_triangle.setOrigin(m_figure_length, m_figure_length);
    m_triangle.setRotation(m_turning_radius);
    m_window->draw(m_triangle);
}