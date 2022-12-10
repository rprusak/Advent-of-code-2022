#ifndef STARTER_DAY9_H
#define STARTER_DAY9_H

#include <string>
#include <vector>

#include "utility"

namespace day9 {
enum class DIRECTION { UP, DOWN, RIGHT, LEFT };

using Motions = std::vector<std::pair<DIRECTION, int>>;
using Point = std::pair<int, int>;

Motions parseInput(const std::vector<std::string>& input);

unsigned calculateTailTravelLength(const Motions& motions);
unsigned calculateTailTravelLength2(const Motions& motions);

}  // namespace day9

#endif  // STARTER_DAY9_H
