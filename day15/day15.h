#ifndef STARTER_DAY15_H
#define STARTER_DAY15_H

#include <string>
#include <utility>
#include <vector>

namespace day15 {

using Point = std::pair<int64_t, int64_t>;
using Entry = std::pair<Point, Point>;

Entry parseLine(const std::string& line);
std::vector<Entry> parseInput(const std::vector<std::string>& input);

unsigned countPositionsWithoutBeaconInLine(const std::vector<std::string>& input,
                                           const int64_t line);
uint64_t calculateTuningFrequency(const std::vector<std::string>& input, const int64_t max);
}  // namespace day15

#endif  // STARTER_DAY15_H