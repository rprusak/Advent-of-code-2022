#ifndef STARTER_DAY16_H
#define STARTER_DAY16_H

#include <map>
#include <string>
#include <vector>
namespace day16 {
using ScanOutput = std::map<std::string, std::pair<unsigned, std::vector<std::string>>>;

std::pair<std::string, std::pair<unsigned, std::vector<std::string>>> parseLine(
    const std::string& line);
ScanOutput parseInput(const std::vector<std::string>& input);

unsigned calculateMostPressurePossible(const std::vector<std::string>& input);
unsigned calculateMostPressurePossibleWithElephant(const std::vector<std::string>& input);
}  // namespace day16

#endif  // STARTER_DAY16_H
