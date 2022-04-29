#include <iostream>
#include <SFML/Graphics.hpp>

void main(int argc, char** argv[]) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "Rendering the rectangle.");
    sf::RectangleShape rectangle(sf::Vector2f(250.0f, 125.0f));
    rectangle.setFillColor(sf::Color::Magenta);
    rectangle.setPosition(320, 240);
    rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);

    while (window.isOpen()) {
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
