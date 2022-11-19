#pragma once
#include "i_drawable.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <random>
#include <sstream>
#include <chrono>
#include <thread>

class World : public iDrawable
{
    private:
        int m_width_window;
        int m_height_window;
        float m_figure_length;
        sf::Color m_color = sf::Color(192, 192, 192);
        std::shared_ptr<sf::RenderWindow> m_window;
        template<class T>
        void addColorPosition(T figure, const float x, const float y, const float origin_x, const float origin_y, const float rotate) const;
        void createTriangle(const float x, const float y) const;
        void createSquare(const float x, const float y) const;
        void createRectangle(const float x, const float y) const;
        void createCircle(const float x, const float y) const;
        void draw() const override;

    public:
        World();
        void startLoop();
};