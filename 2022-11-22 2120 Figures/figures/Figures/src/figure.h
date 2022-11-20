#pragma once
#include "i_drawable.h"

template <class Type>
class Figure : public iDrawable
{
private:
    float m_dx;
    float m_dy;
    float m_side_length;
    float m_angle_rotation;
    const std::shared_ptr<sf::RenderWindow> m_window;
    Type m_figure;  // объект фигуры
    sf::Color m_color;

public:
    Figure::Figure(const float x, const float y, const float side_length, const Type figure, const std::shared_ptr<sf::RenderWindow> window, const sf::Color color, const float angle_rotation)
        : m_dx(x), m_dy(y), m_side_length(side_length), m_figure(figure), m_window(window), m_color(color), m_angle_rotation(angle_rotation)
    {
    }
    void Figure::draw() override
    {
        m_figure.setFillColor(m_color);
        m_figure.setPosition(m_dx, m_dy);
        m_figure.setOrigin(m_side_length, m_side_length);
        m_figure.setRotation(m_angle_rotation);
        m_window->draw(m_figure);
    }
};