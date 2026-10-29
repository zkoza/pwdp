#ifndef KOMPUTER_H
#define KOMPUTER_H

#include "plansza.h"

#include <random>

class Komputer
{
  public:
    Komputer(const Plansza & plansza);
    Move    make_move() const;

    Move first_move() const;
  private:
    Move best_move(Plansza::Pole pole) const;
    Move random_move() const;
    Move special_move() const;

    const Plansza& _plansza;
    mutable std::mt19937 rng;
};

#endif  // KOMPUTER_H
