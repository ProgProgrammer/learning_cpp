#include <iostream>
#include "time.h"
#include <SFML/Graphics.hpp>
#include "classes_mover_interface.h"

void main(int argc, char** argv[])
{
    int weight_screen = 640;
    int height_screen = 480;
    float weight_rectangle = 250;
    float height_rectangle = 125;
    int x = 320;
    int y = 240;
    int speed = 1;

    RectangleMover * rectangle_mover = new RectangleMover(x, y, speed, weight_screen, height_screen,
        weight_rectangle, height_rectangle);

    sf::RenderWindow window(sf::VideoMode(weight_screen, height_screen), "Rendering the rectangle.");
    sf::RectangleShape rectangle(sf::Vector2f(weight_rectangle, height_rectangle));
    rectangle.setFillColor(sf::Color::Magenta);
    rectangle.setPosition(x, y);
    rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);

    std::cout << "The local time is: " << getSeconds();

    while (window.isOpen()) {
        if (getSeconds() % 5 == 0)
        {
            static int num = 1;

            srand((unsigned int)time(NULL));

            if (num % 2)
            {
                rectangle_mover->Calculate(rand() % 3 - 1, "x");
                x = rectangle_mover->GetX();
                num++;
            }
            else
            {
                rectangle_mover->Calculate(rand() % 3 - 1, "y");
                y = rectangle_mover->GetY();
                num++;
            }

            rectangle.setPosition(x, y);
            rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
        }

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue);
        window.draw(rectangle); // Drawing our shape.
        window.display();
    }
}
