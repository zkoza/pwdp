#include "widok.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>
#include <iostream>
#include <print>

Widok::Widok(const Plansza &plansza)
    : _plansza{plansza},
      _window(get_video_mode(), L"KiK", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed,
              sf::ContextSettings{.antiAliasingLevel = 8})
{
    // sf::ContextSettings settings;
    // settings.antiAliasingLevel = 8;
    auto rec = sf::VideoMode::getDesktopMode().size;
    int x = (rec.x - 3 * _field_height) / 2;
    int y = (rec.y - 3 * _field_height - _status_bar_height) / 2;

    _window.setPosition(sf::Vector2i(x, y));
    _window.display();
    display();
}

void Widok::display()
{
    sf::Color background_color(255, 228, 181);
    sf::Color frame_color(122, 78, 0);
    sf::Font font("arial.ttf");
    _window.clear(frame_color);
    //   auto size = _window.getSize();
    sf::RectangleShape rectangle(sf::Vector2f(_field_height, _field_height));
    rectangle.setFillColor(background_color);
    rectangle.setOutlineColor(frame_color);
    rectangle.setOutlineThickness(1);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            float x = i * _field_height;
            float y = j * _field_height;
            rectangle.setPosition(sf::Vector2f(x, y));
            _window.draw(rectangle);
            auto stan_pola = _plansza.get_state()[i][j];
            if (stan_pola == Plansza::Pole::computer)
                draw_cicle(i, j);
            else if (stan_pola == Plansza::Pole::human)
                draw_cross(i, j);
        }
    draw_status_bar();
    draw_status_bar_result();
    draw_restart();
    _window.display();
}

void Widok::process_event(const std::optional<sf::Event> &event)
{
    //   assert (!has_move());
    if (event->is<sf::Event::Closed>())
    {
        std::cout << "close event\n";
        _close = true;
        return;
    }
    const sf::Event::MouseButtonPressed *mouse = event->getIf<sf::Event::MouseButtonPressed>();
    if (mouse != nullptr)
    {
        //        std::cout << "mouse\n";
        if (mouse->button != sf::Mouse::Button::Left)
            return;
        auto pos = mouse->position;
        int x = pos.x / _field_height;
        int y = pos.y / _field_height;
        //       std::println("mose left: pos = {}, {}; x = {}, y = {}", pos.x, pos.y, x, y);
        if (_game_is_active)
        {
            if (x >= 3 || y >= 3)
                return;
            assert(x >= 0 && y >= 0);
            if (_plansza.get_state()[x][y] != Plansza::Pole::empty)
                return;
            _move.first = x;
            _move.second = y;
            _move_requested = true;
            //        std::cout << "move calculated as (" << x << ", " << y << ")\n";
            return;
        }
        else
        {
            if (x == 2 && y == 3)
            {
                _new_game_requested = true;
                return;
            }
        }
    }

    //    std::cout << "other event\n";
}

bool Widok::has_move() const
{
    return _move_requested;
}

Move Widok::pop_move()
{
    _move_requested = false;
    return _move;
}

sf::VideoMode Widok::get_video_mode()
{
    int window_width = sf::VideoMode::getDesktopMode().size.x;
    int window_height = sf::VideoMode::getDesktopMode().size.y - _status_bar_height;
    int size = std::min(window_height, window_width);
    size /= 4;
    _field_height = size;
    size *= 3;
    window_width = size;
    window_height = size + _status_bar_height;

    const auto video_mode = sf::VideoMode(sf::Vector2u(window_width, window_height));
    return video_mode;
}

void Widok::draw_cicle(int x, int y)
{
    std::println("{}, x = {}, y = {}", __FUNCTION__, x, y);
    float radius = _field_height / 3.0f;
    float dx = (_field_height - 2 * radius) / 2;
    sf::CircleShape circle(radius, 60);

    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color(250, 150, 100));
    circle.setOutlineThickness(4);
    sf::Vector2f position;
    position.x = x * _field_height + dx;
    position.y = y * _field_height + dx;
    circle.setPosition(position);
    _window.draw(circle);
}

void Widok::draw_cross(int x, int y)
{
    std::println("{}, x = {}, y = {}", __FUNCTION__, x, y);
    float radius = _field_height / 3.0f;
    float dx = (_field_height - 2 * radius) / 2;
    float length = 2 * radius * std::sqrt(2.0);
    sf::RectangleShape line({4.0f, length});
    line.rotate(sf::degrees(-45));

    line.setFillColor(sf::Color::Transparent);
    line.setFillColor(sf::Color(250, 150, 100));
    sf::Vector2f position;
    position.x = x * _field_height + dx;
    position.y = y * _field_height + dx;
    line.setPosition(position);
    _window.draw(line);
    line.rotate(sf::degrees(90));
    position.x = (x + 1) * _field_height - dx;
    line.setPosition(position);
    _window.draw(line);
}

void Widok::draw_status_bar()
{
    sf::Font font("arial.ttf");
    sf::Text text(font);
    text.setString(_status_message);
    text.setCharacterSize(_status_bar_height - 4);
    text.setPosition({10.0f, 3.0f * _field_height});
    _window.draw(text);
}

void Widok::draw_status_bar_result()
{
    sf::Font font("arial.ttf");
    sf::Text text(font);
    text.setString(_status_numerical_result);
    text.setCharacterSize(_status_bar_height - 4);
    text.setPosition({10.0f + _field_height, 3.0f * _field_height});
    _window.draw(text);
}

void Widok::draw_restart()
{
    if (_game_is_active)
        return;

    sf::Font font("arial.ttf");
    sf::Text text(font);
    text.setString("Kolejna gra");
    text.setFillColor(sf::Color::Yellow);
    text.setCharacterSize(_status_bar_height - 4);
    text.setStyle(sf::Text::Underlined);
    text.setPosition({10.0f + 2 * _field_height, 3.0f * _field_height});
    _window.draw(text);
}
