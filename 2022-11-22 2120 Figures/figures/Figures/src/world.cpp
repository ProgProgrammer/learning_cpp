#include "world.h"

void World::createTriangle(const float x, const float y) const
{
    sf::RectangleShape rec_shape = sf::RectangleShape(sf::Vector2f(m_figure_length, m_figure_length));
    rec_shape.setOrigin(rec_shape.getSize().x, rec_shape.getSize().y);
    sf::CircleShape triangle(m_figure_length, 3);
    triangle.setFillColor(m_color);
    triangle.setPosition(x, y);
    triangle.setOrigin(m_figure_length, m_figure_length);
    m_window->draw(triangle);
}

void World::createSquare(const float x, const float y) const
{
    sf::CircleShape square(m_figure_length, 4);
    square.setFillColor(m_color);
    square.setPosition(x, y);
    square.setRotation(-45.f);
    square.setOrigin(m_figure_length, m_figure_length);
    m_window->draw(square);
}

void World::createRectangle(const float x, const float y) const
{
    sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(m_figure_length + m_figure_length, m_figure_length));
    rectangle.setFillColor(m_color);
    rectangle.setPosition(x, y);
    rectangle.setOrigin(rectangle.getSize().x, rectangle.getSize().y);
    m_window->draw(rectangle);
}

void World::createCircle(const float x, const float y) const
{
    sf::CircleShape circle(m_figure_length);
    circle.setFillColor(m_color);
    circle.setPosition(x, y);
    circle.setOrigin(m_figure_length, m_figure_length);
    m_window->draw(circle);
}

void World::draw() const
{
    m_window->clear();

    createTriangle(150, 150);
    createSquare(450, 150);
    createRectangle(850, 150);
    createCircle(1050, 150);
    createTriangle(1050, 450);
    createSquare(850, 450);
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