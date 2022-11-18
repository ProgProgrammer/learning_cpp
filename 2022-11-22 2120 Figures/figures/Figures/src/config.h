#pragma once
#include <SFML/Graphics.hpp>

class Config
{
    public:
        int m_dx;
        int m_dy;
        int m_width_window;
        int m_height_window;
        Config(const int x, const int y, const int width_window, const int height_window) : m_dx(x), m_dy(y), m_width_window(width_window), m_height_window(height_window)
        {
        }
};