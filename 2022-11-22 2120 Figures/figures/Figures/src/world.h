#pragma once
#include "i_drawable.h"
#include "circle.h"
#include "rectangle.h"
#include "square.h"
#include "triangle.h"
#include <SFML/Graphics.hpp>

class World : public IDrawable
{
    private:
        int m_width_window;
        int m_height_window;
        sf::Color m_color = sf::Color(192, 192, 192);
        std::shared_ptr<sf::RenderWindow> m_window;
        std::vector<std::shared_ptr<IDrawable>> m_figures;
        void draw() override;

    public:
        World();
        void startLoop();
};