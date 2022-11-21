#include "world.h"
#include <chrono>
#include <thread>

void World::draw()
{
    m_window->clear();

    for (int i = 0; i < m_figures.size(); i++)
    {
        m_figures[i]->draw();
    }

    m_window->display();
}

World::World()
{
    m_width_window = 1200;
    m_height_window = 600;
    m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(m_width_window, m_height_window), "Figures");
}

void World::startLoop()
{
    float angle_rotation = -45;
    float w_h = 100;  // ширина и высота фигур, кроме квадрата
    float w_h_square = 125;  // ширина и высота квадрата
    float w_rectangle = 200;  // ширина квадрата
    float h_rectangle = 100;  // высота квадрата

    m_figures.push_back(std::make_shared<Triangle>(150, 150, w_h, w_h, m_window, m_color));
    m_figures.push_back(std::make_shared<Square>(400, 150, w_h_square, w_h_square, m_window, m_color, angle_rotation));
    m_figures.push_back(std::make_shared<Rectangle>(750, 150, w_rectangle, h_rectangle, m_window, m_color));
    m_figures.push_back(std::make_shared<Circle>(1050, 150, w_h, w_h, m_window, m_color));
    m_figures.push_back(std::make_shared<Triangle>(1050, 450, w_h, w_h, m_window, m_color));
    m_figures.push_back(std::make_shared<Square>(800, 450, w_h_square, w_h_square, m_window, m_color, angle_rotation));
    m_figures.push_back(std::make_shared<Rectangle>(550, 450, w_rectangle, h_rectangle, m_window, m_color));
    m_figures.push_back(std::make_shared<Circle>(150, 450, w_h, w_h, m_window, m_color));

    while (m_window->isOpen())
    {
        using namespace std::chrono_literals;
        auto start = std::chrono::high_resolution_clock::now();

        sf::Event event;
        m_window->pollEvent(event);

        draw();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::this_thread::sleep_for(40ms - elapsed); // TODO 40ms to config

        if (event.type == sf::Event::Closed)
            m_window->close();
    }
}