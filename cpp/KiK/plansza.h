#ifndef PLANSZA_H
#define PLANSZA_H

#include "move.h"

#include <array>

class Plansza
{
  public:
    enum class Pole : char
    {
        empty = ' ',
        computer = 'O',
        human = 'X'
    };
    constexpr static int N = 3;
    using State = std::array<std::array<Pole, N>, N>;

    Plansza();
    Result move_human(Move move);
    Result move_computer(Move move);
    State const& get_state() const { return _state; }
    Result result() const { return _result; }
    void new_game();
    int score (Plansza::Pole pole) const;
    int moves() const { return _moves; }
  private:
    Result calculate_result(Pole pole) const;

    Result _result = Result::unknown;
    State _state;
    int _moves = 0;
};



#endif  // PLANSZA_H
