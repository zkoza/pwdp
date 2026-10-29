#include "plansza.h"
#include <cassert>
#include <stdexcept>

Plansza::Plansza()
{
    new_game();
}

Result Plansza::move_human(Move move)
{
    int y = move.first;
    int x = move.second;
    assert(x >= 0 && x < 3);
    assert(y >= 0 && y < 3);
    _state[y][x] = Pole::human;
    _result = calculate_result(Pole::human);
    _moves++;
    return _result;
}

Result Plansza::move_computer(Move move)
{
    int y = move.first;
    int x = move.second;
    assert(x >= 0 && x < 3);
    assert(y >= 0 && y < 3);
    _state[y][x] = Pole::computer;
    _result = calculate_result(Pole::computer);
    _moves++;
    return _result;
}

void Plansza::new_game()
{
    for (auto& row : _state)
        for (auto& x : row)
            x = Pole::empty;
    _result = Result::unknown;
    _moves = 0;
}

Result Plansza::calculate_result(Pole pole) const
{
    Result result = Result::unknown;

    int pionki = 0;
    for (const auto row : _state)
        for (const auto pole : row)
        {
            pionki += pole != Pole::empty;
        }

    int mx = 0;
    int diag1 = 0;
    int diag2 = 0;
    for (int i = 0; i < 3; i++)
    {
        int s = 0;
        int t = 0;
        for (int j = 0; j < 3; j++)
        {
            if (_state[i][j] == pole)
                s++;
            if (_state[j][i] == pole)
                t++;
        }
        if (_state[i][i] == pole)
            diag1++;
        if (_state[i][2 - i] == pole)
            diag2++;

        mx = std::max(mx, s);
        mx = std::max(mx, t);
    }
    mx = std::max(mx, diag1);
    mx = std::max(mx, diag2);
    assert(mx >= 0 && mx <= 3);
    if (mx != 3)
    {
        if (pionki != 9)
            return Result::unknown;
        return Result::draw;
    }
    if (pole == Pole::computer)
        return Result::computer_wins;
    else if (pole == Pole::human)
        return Result::human_wins;
    else
        throw std::invalid_argument("Plansza::result called with an invalid argument");
}

int Plansza::score(Pole czyj_ruch) const
{
    int result = 0;
    std::array<int, 4> tab = {0, 100, 10'000, 1'000'000};
    int diag1 = 0;
    int diag2 = 0;
    for (int y = 0; y < 3; y++)
    {
        int in_row = 0;
        for (int x = 0; x < 3; x++)
        {
            if (_state[y][x] == czyj_ruch)
                in_row++;
            else if (_state[y][x] != Plansza::Pole::empty)
            {
                in_row = 0;
                break;
            }
        }
        result += tab[in_row];
    }

    for (int y = 0; y < 3; y++)
    {
        int in_column = 0;
        for (int x = 0; x < 3; x++)
        {
            auto stan_pola = _state[x][y];
            if (stan_pola == czyj_ruch)
                in_column++;
            else if (stan_pola != Plansza::Pole::empty)
            {
                in_column = 0;
                break;
            }
        }
        result += tab[in_column];
    }

    for (int y = 0; y < 3; y++)
    {
        auto stan_pola = _state[y][y];
        if (stan_pola == czyj_ruch)
            diag1++;
        else if (stan_pola != Plansza::Pole::empty)
        {
            diag1 = 0;
            break;
        }
    }
    result += tab[diag1];

    for (int y = 0; y < 3; y++)
    {
        auto stan_pola = _state[y][2 - y];
        if (stan_pola == czyj_ruch)
            diag2++;
        else if (stan_pola != Plansza::Pole::empty)
        {
            diag2 = 0;
            break;
        }
    }
    result += tab[diag2];
    return result;
}
