#include "komputer.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <ctime>
#include <numeric>
#include <print>
#include <stdexcept>


Komputer::Komputer(const Plansza& plansza)
    : _plansza(plansza)
{
    rng.seed(std::time(nullptr));
}

Move Komputer::make_move() const
{
    Move move = best_move(Plansza::Pole::computer);
    return move;
}

Move Komputer::first_move() const
{
    std::uniform_real_distribution<double> distr(0.0, 1.0);

    std::array<double, 9> prob{3, 2, 3, 2, 1, 2, 3, 2, 1};
    double sum = std::accumulate(begin(prob), end(prob), 0.0);
    std::ranges::for_each(prob, [sum](double& x) { x /= sum; });

    for (int i = 1; i < prob.size(); i++)
    {
        prob[i] += prob[i - 1];
    }
    prob[8] = 1.0;
    double value = distr(rng);
    int idx = 0;
    for (; idx < prob.size(); idx++)
    {
        if (value < prob[idx])
            break;
    }
    assert(idx >= 0 && idx < 9);
    return Move(idx / 3, idx % 3);
}

Move Komputer::best_move(Plansza::Pole pole) const
{
    if (_plansza.moves() == 2 && _plansza.get_state()[1][1] != Plansza::Pole::empty)
    {
        Move sm = special_move();
        std::println("special move, x: {} y: {}", sm.first, sm.second);
        return sm;
    }
    assert(pole == Plansza::Pole::computer || pole == Plansza::Pole::human);
    const Plansza::Pole other = (pole == Plansza::Pole::computer) ? Plansza::Pole::human : Plansza::Pole::computer;
    int best_x = 0;
    int best_y = 0;
    int best_score = -1;
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            if (_plansza.get_state()[y][x] != Plansza::Pole::empty)
                continue;

            Plansza plansza = _plansza;
            plansza.move_computer({y, x});
            int sc = plansza.score(pole);

            plansza = _plansza;
            plansza.move_human({y, x});
            int sh = plansza.score(other);

            std::println("x={} y={} sc={} sh={}", x, y, sc, sh);

            sc = 4* sc + sh;

            if (sc > best_score)
            {
                best_score = sc;
                best_x = x;
                best_y = y;
            }
        }
    }
    std::println("score: {} x: {} y: {}", best_score, best_x, best_y);
    return {best_y, best_x};
}

Move Komputer::random_move() const
{
    const int MAX = 4000;  // zabezpieczenie przed nieskończoną pętlą
    std::uniform_int_distribution<int> distr(0, 2);
    for (int i = 0; i < MAX; i++)
    {
        int x = distr(rng);
        int y = distr(rng);
        assert(x >= 0 && x < 3);
        assert(y >= 0 && y < 3);

        if (_plansza.get_state()[x][y] != Plansza::Pole::empty)
            continue;
        std::println("make_move: x = {}, y = {}", x, y);
        return {x, y};
    }
    throw std::logic_error("failed to find an empty field");
}

Move Komputer::special_move() const
{
    assert(_plansza.moves() == 2);
    assert(_plansza.get_state()[1][1] != Plansza::Pole::empty);
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            if (y == 1 && x == 1)
                continue;
            if (_plansza.get_state()[y][x] != Plansza::Pole::empty)
            {
                return {2-y, 2-x};
            }
        }
    }
    throw std::logic_error("Logic error in special_move");
}
