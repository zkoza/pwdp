#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    bool visible_shape = true;
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), L"Moje okno z kółkiem");
    sf::CircleShape shape(198.7, 60);
    shape.setFillColor(sf::Color::Red);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                visible_shape = !visible_shape;
        }
        window.clear(sf::Color::Black);
        if (visible_shape)
            window.draw(shape);
        window.display();
    }
}
