#include "world.h"

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
    m_window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(m_width_window, m_height_window), "Figures"));
}

void World::startLoop()
{
    float turning_radius = -45;

    m_figures.push_back(std::shared_ptr<iDrawable>(new Triangle(150, 150, 100, m_window, m_color)));
    m_figures.push_back(std::shared_ptr<iDrawable>(new Square(400, 150, 125, m_window, m_color, turning_radius)));
    m_figures.push_back(std::shared_ptr<iDrawable>(new Rectangle(750, 150, 100, m_window, m_color)));
    m_figures.push_back(std::shared_ptr<iDrawable>(new Circle(1050, 150, 100, m_window, m_color)));
    m_figures.push_back(std::shared_ptr<iDrawable>(new Triangle(1050, 450, 100, m_window, m_color)));
    m_figures.push_back(std::shared_ptr<iDrawable>(new Square(800, 450, 125, m_window, m_color, turning_radius)));
    m_figures.push_back(std::shared_ptr<iDrawable>(new Rectangle(550, 450, 100, m_window, m_color)));
    m_figures.push_back(std::shared_ptr<iDrawable>(new Circle(150, 450, 100, m_window, m_color)));

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