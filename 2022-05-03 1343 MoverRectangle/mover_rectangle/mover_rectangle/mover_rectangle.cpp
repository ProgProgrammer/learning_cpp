#include <iostream>
#include <SFML/Graphics.hpp>
#include "classes_mover_interface.h"
#include "class_projectiler_mover.h"

int main()
{
    int weight_screen = 700;
    int height_screen = 500;
    int weight_rectangle = 100;
    int height_rectangle = 100;
    int x = 350;
    int y = 250;
    int speed = 50;
    int timeStamp = 1;

    int w_projectiler, h_projectiler;
    w_projectiler = h_projectiler = 10;
    int x_projectiler, y_projectiler;
    int speed_projectiler = 1;

    RectangleMover * rectangle_mover = new RectangleMover(x, y, speed, timeStamp, weight_screen, height_screen,
        weight_rectangle, height_rectangle);

    sf::RenderWindow window(sf::VideoMode(weight_screen, height_screen), "Rendering the rectangle.");
    sf::RectangleShape rectangle(sf::Vector2f(weight_rectangle, height_rectangle));
    rectangle.setFillColor(sf::Color::Magenta);
    rectangle.setPosition(x, y);
    rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W)
                {
                    rectangle_mover->CalculateYU();
                    y = rectangle_mover->GetY();
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    rectangle_mover->CalculateYD();
                    y = rectangle_mover->GetY();
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    rectangle_mover->CalculateXU();
                    x = rectangle_mover->GetX();
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    rectangle_mover->CalculateXD();
                    x = rectangle_mover->GetX();
                }

                rectangle.setPosition(x, y);
                rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    x_projectiler = rectangle_mover->GetX();
                    y_projectiler = rectangle_mover->GetY() - 55;

                    sf::RectangleShape projectiler(sf::Vector2f(w_projectiler, h_projectiler));
                    projectiler.setFillColor(sf::Color::Red);
                    projectiler.setPosition(x_projectiler, y_projectiler);
                    projectiler.setOrigin(projectiler.getSize().x / 2, projectiler.getSize().y / 2);
                    window.draw(projectiler); // Drawing our shape.
                    window.display();

                    ProjectilerMover * projectiler_mover = new ProjectilerMover(window, projectiler, rectangle,
                        x_projectiler, y_projectiler, speed_projectiler, timeStamp, weight_screen, height_screen, 
                        w_projectiler, h_projectiler);

                    projectiler_mover->CalculateYU();

                    delete projectiler_mover;
                }
            }
        }

        window.clear(sf::Color::Blue);
        window.draw(rectangle); // Drawing our shape.
        window.display();
    }

    delete rectangle_mover;

    return 0;
}
