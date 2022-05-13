#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "classes_mover_interface.h"
#include "class_projectiler_mover.h"
#include "static_objects.h"

struct projMov
{
    int w_projectiler;
    int h_projectiler;
    int x_projectiler;
    int y_projectiler;
    int speed_projectiler;
};

struct recMov
{
    int weight_screen;
    int height_screen;
    int weight_rectangle;
    int height_rectangle;
    int x;
    int y;
    int speed;
    int timeStamp;
};

void projtlerMover(projMov & pm, recMov & rm, sf::RenderWindow & window, sf::RectangleShape & rectangle, RectangleMover * rectangle_mover, 
    std::vector<StaticObjects> & st_objects, std::vector<sf::RectangleShape> & rs_objs)
{
    pm.x_projectiler = rectangle_mover->GetX();
    pm.y_projectiler = rectangle_mover->GetY() - 55;

    sf::RectangleShape projectiler(sf::Vector2f(pm.w_projectiler, pm.h_projectiler));
    projectiler.setFillColor(sf::Color::Red);
    projectiler.setPosition(pm.x_projectiler, pm.y_projectiler);
    projectiler.setOrigin(projectiler.getSize().x / 2, projectiler.getSize().y / 2);
    window.draw(projectiler); // Drawing our shape.
    window.display();

    ProjectilerMover * projectiler_mover = new ProjectilerMover(window, projectiler, rectangle, st_objects, rs_objs,
        pm.x_projectiler, pm.y_projectiler, pm.speed_projectiler, rm.timeStamp, rm.weight_screen, rm.height_screen,
        pm.w_projectiler, pm.h_projectiler);

    projectiler_mover->CalculateYU();

    delete projectiler_mover;
}

int main()
{
    recMov rm;
    rm.weight_screen = 700;
    rm.height_screen = 500;
    rm.weight_rectangle = 100;
    rm.height_rectangle = 100;
    rm.x = 350;
    rm.y = 250;
    rm.speed = 50;
    rm.timeStamp = 1;

    projMov pm;
    pm.w_projectiler = pm.h_projectiler = 10;
    pm.speed_projectiler = 1;

    RectangleMover * rectangle_mover = new RectangleMover(rm.x, rm.y, rm.speed, rm.timeStamp, rm.weight_screen, rm.height_screen,
        rm.weight_rectangle, rm.height_rectangle);

    std::vector<StaticObjects> st_objects;    // массив координат и размеров статических объектов
    std::vector<sf::RectangleShape> rs_objs;  // массив для отрисовки статических объектов

    sf::RenderWindow window(sf::VideoMode(rm.weight_screen, rm.height_screen), "Rendering the rectangle.");
    sf::RectangleShape * rectangle = new sf::RectangleShape(sf::Vector2f(rm.weight_rectangle, rm.height_rectangle));

    if (window.isOpen())
    {
        rectangle->setFillColor(sf::Color::Magenta);
        rectangle->setPosition(rm.x, rm.y);
        rectangle->setOrigin(rectangle->getSize().x / 2, rectangle->getSize().y / 2);

        st_objects.push_back(StaticObjects(100, 100, 50, 50));
        st_objects.push_back(StaticObjects(100, 100, 200, 150));

        for (int i = 0; i < 2; i++)
        {
            rs_objs.push_back(sf::RectangleShape(sf::Vector2f(st_objects[i].GetW(), st_objects[i].GetH())));
            rs_objs[i].setFillColor(sf::Color::Cyan);
            rs_objs[i].setPosition(st_objects[i].GetX(), st_objects[i].GetY());
            rs_objs[i].setOrigin(rs_objs[i].getSize().x / 2, rs_objs[i].getSize().y / 2);
        }
    }

    while (window.isOpen()) 
    {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W)
                {
                    rectangle_mover->CalculateYU();
                    rm.y = rectangle_mover->GetY();
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    rectangle_mover->CalculateYD();
                    rm.y = rectangle_mover->GetY();
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    rectangle_mover->CalculateXU();
                    rm.x = rectangle_mover->GetX();
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    rectangle_mover->CalculateXD();
                    rm.x = rectangle_mover->GetX();
                }


                rectangle->setPosition(rm.x, rm.y);
                rectangle->setOrigin(rectangle->getSize().x / 2, rectangle->getSize().y / 2);
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                projtlerMover(pm, rm, window, *rectangle, rectangle_mover, st_objects, rs_objs);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    projtlerMover(pm, rm, window, *rectangle, rectangle_mover, st_objects, rs_objs);
                }
            }
        }

        window.clear(sf::Color::Blue);
        window.draw(*rectangle); // Drawing our shape.

        for (int i = 0; i < rs_objs.size(); i++)
        {
            window.draw(rs_objs[i]);
        }

        window.display();
    }

    delete rectangle_mover;
    delete rectangle;

    return 0;
}
