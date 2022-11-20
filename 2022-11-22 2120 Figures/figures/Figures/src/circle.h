#pragma once
#include "i_drawable.h"

class Circle : public iDrawable
{
private:
    float m_dx;
    float m_dy;
    float m_figure_length;
    float m_turning_radius;
    const std::shared_ptr<sf::RenderWindow> m_window;
    sf::CircleShape m_circle;
    sf::Color m_color;

public:
    Circle(const float x, const float y, const float length, const std::shared_ptr<sf::RenderWindow> window, const sf::Color color, const float turning_radius = 0);
    void draw() override;
};