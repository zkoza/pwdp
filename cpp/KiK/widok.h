#ifndef WIDOK_H
#define WIDOK_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "move.h"
#include "plansza.h"

class Widok
{
  public:
    Widok(const Plansza& plansza);
    void display();
    void process_event(const std::optional<sf::Event>& event);
    bool close_requested() { return _close; }
    bool new_game_requested() { return _new_game_requested; }
    bool has_move() const;
    Move pop_move();
    sf::RenderWindow& window() { return _window; }
    void clear_event_store()
    {
        _close = false;
        _move_requested = false;
    }
    void set_status_msg(const std::wstring& msg) { _status_message = msg; }
    void set_numerical_result_msg(int cwins, int hwins, int sraws)
    {
        std::wstring msg = std::format(L"silikion-białko: {}-{}", cwins, hwins);
        _status_numerical_result = msg;
    }
    void enable_game(bool active)
    {
        _game_is_active = active;
        _new_game_requested = false;
    }
    void clear_status_bar()
    {
        _status_message.clear();
        _status_numerical_result.clear();
    }

  private:
    sf::VideoMode get_video_mode();
    void draw_cicle(int x, int y);
    void draw_cross(int x, int y);
    void draw_status_bar();
    void draw_status_bar_result();
    void draw_restart();

    const int _status_bar_height = 25;
    const Plansza& _plansza;
    sf::RenderWindow _window;
    int _field_height;

    bool _close = false;
    bool _move_requested = false;
    bool _new_game_requested = false;
    Move _move = {-1, -1};
    bool _game_is_active = true;

    std::wstring _status_message;
    std::wstring _status_numerical_result;
};

#endif  // WIDOK_H
