#include "world.h"

template<class T>
void World::addColorPosition(T figure, const float x, const float y, const float origin_x, const float origin_y, const float rotate) const
{
    figure.setFillColor(m_color);
    figure.setPosition(x, y);
    figure.setOrigin(origin_x, origin_y);
    figure.setRotation(rotate);
    m_window->draw(figure);
}

void World::createTriangle(const float x, const float y) const
{
    sf::CircleShape triangle(m_figure_length, 3);
    const float rotate = 0;
    addColorPosition(triangle, x, y, m_figure_length, m_figure_length, rotate);
}

void World::createSquare(const float x, const float y) const
{
    sf::CircleShape square(m_figure_length, 4);
    const float rotate = -45;
    addColorPosition(square, x, y, m_figure_length, m_figure_length, rotate);
}

void World::createRectangle(const float x, const float y) const
{
    sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(m_figure_length + m_figure_length, m_figure_length));
    const float rotate = 0;
    addColorPosition(rectangle, x, y, m_figure_length, m_figure_length, rotate);
}

void World::createCircle(const float x, const float y) const
{
    sf::CircleShape circle(m_figure_length);
    const float rotate = 0;
    addColorPosition(circle, x, y, m_figure_length, m_figure_length, rotate);
}

void World::draw() const
{
    m_window->clear();

    createTriangle(150, 150);
    createSquare(450, 150);
    createRectangle(750, 150);
    createCircle(1050, 150);
    createTriangle(1050, 450);
    createSquare(750, 450);
    createRectangle(550, 450);
    createCircle(150, 450);

    m_window->display();
}

World::World()
{
    m_figure_length = 100;
    m_width_window = 1200;
    m_height_window = 600;
    m_window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(m_width_window, m_height_window), "Figures"));
}

void World::startLoop()
{
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