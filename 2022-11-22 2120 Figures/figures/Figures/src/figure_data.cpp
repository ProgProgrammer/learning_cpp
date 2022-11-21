#include "figure_data.h"

FigureData::FigureData(const float x, const float y, const float width, const float height,
    const std::shared_ptr<sf::RenderWindow> window, const sf::Color color, const float angle_rotation) 
    : m_dx(x), m_dy(y), m_w(width), m_h(height), m_window(window), m_color(color), m_angle_rotation(angle_rotation)
{
}

void FigureData::drawFigureTemplate(sf::CircleShape figure)
{
    figure.setFillColor(m_color);
    figure.setPosition(m_dx, m_dy);
    figure.setOrigin(m_w, m_h);
    figure.setRotation(m_angle_rotation);
    m_window->draw(figure);
}

void FigureData::drawFigureTemplate(sf::RectangleShape figure)
{
    figure.setFillColor(m_color);
    figure.setPosition(m_dx, m_dy);
    figure.setOrigin(m_w, m_h);
    figure.setRotation(m_angle_rotation);
    m_window->draw(figure);
}