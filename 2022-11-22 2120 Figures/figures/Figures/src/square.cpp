#include "square.h"

Square::Square(const float x, const float y, const float length, const std::shared_ptr<sf::RenderWindow> window, const sf::Color color, const float turning_radius)
    : m_dx(x), m_dy(y), m_figure_length(length), m_window(window), m_color(color), m_turning_radius(turning_radius)
{
    m_square = sf::CircleShape(m_figure_length, 4);
}

void Square::draw()
{
    m_square.setFillColor(m_color);
    m_square.setPosition(m_dx, m_dy);
    m_square.setOrigin(m_figure_length, m_figure_length);
    m_square.setRotation(m_turning_radius);
    m_window->draw(m_square);
}