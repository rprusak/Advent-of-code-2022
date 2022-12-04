#include "day4.h"

#include <regex>

namespace day4 {
const std::regex PATTERN{R"#(^(\d+)-(\d+),(\d+)-(\d+)$)#"};

Entry parseLine(const std::string &line) {
    std::smatch matchResult;
    if (!std::regex_match(line, matchResult, PATTERN))
        throw std::runtime_error{"Could not parse line: " + line};

    Entry result;

    result.first.first = std::stoul(matchResult[1].str());
    result.first.second = std::stoul(matchResult[2].str());
    result.second.first = std::stoul(matchResult[3].str());
    result.second.second = std::stoul(matchResult[4].str());

    return result;
}
unsigned countContainedRanges(const std::vector<std::string> &input) {
    unsigned result{0};

    for (const auto &line : input) {
        const auto entry = parseLine(line);

        if (entry.first.containsRange(entry.second) || entry.second.containsRange(entry.first))
            result++;
    }

    return result;
}
unsigned countOverlappingRanges(const std::vector<std::string> &input) {
    unsigned result{0};

    for (const auto &line : input) {
        const auto entry = parseLine(line);

        if (entry.first.overlapRange(entry.second)) result++;
    }

    return result;
}

bool Range::containsRange(const Range &otherRange) const {
    return this->first <= otherRange.first && this->second >= otherRange.second;
}
bool Range::overlapRange(const Range &otherRange) const {
    if (containsRange(otherRange) || otherRange.containsRange(*this)) return true;

    return (otherRange.first <= this->second && otherRange.second >= this->second) ||
           (this->first <= otherRange.second && this->second >= otherRange.second);
}
}  // namespace day4
