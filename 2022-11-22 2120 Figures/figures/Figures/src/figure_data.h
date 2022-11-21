#pragma once
#include "i_drawable.h"
#include <SFML/Graphics.hpp>

class FigureData : public IDrawable
{
private:
    float m_dx;
    float m_dy;
    float m_w;
    float m_h;
    float m_angle_rotation;
    const std::shared_ptr<sf::RenderWindow> m_window;
    sf::Color m_color;

public:
    FigureData(const float x, const float y, const float width, const float height,
        const std::shared_ptr<sf::RenderWindow> window, const sf::Color color, const float angle_rotation = 0);
    void drawFigureTemplate(sf::CircleShape figure);
    void drawFigureTemplate(sf::RectangleShape figure);
};