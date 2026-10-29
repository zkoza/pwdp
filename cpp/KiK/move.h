#ifndef MOVE_H
#define MOVE_H

#include <utility>


using Move = std::pair<int, int>;

enum Result
{
    unknown,
    computer_wins,
    human_wins,
    draw
};

#endif  // MOVE_H
