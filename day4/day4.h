#ifndef STARTER_DAY4_H
#define STARTER_DAY4_H

#include <string>
#include <utility>
#include <vector>

namespace day4 {
class Range : public std::pair<unsigned, unsigned> {
  public:
    using std::pair<unsigned, unsigned>::pair;

    bool containsRange(const Range& otherRange) const;
    bool overlapRange(const Range& otherRange) const;
};

using Entry = std::pair<Range, Range>;

Entry parseLine(const std::string& line);

unsigned countContainedRanges(const std::vector<std::string>& input);
unsigned countOverlappingRanges(const std::vector<std::string>& input);

}  // namespace day4

#endif  // STARTER_DAY4_H