#include <iostream>
#include <map>

#include "common.h"
#include "day15.h"

[[maybe_unused]] unsigned part1(const std::vector<std::string> &input, const int line) {
    return day15::countPositionsWithoutBeaconInLine(input, line);
}

unsigned part2(const std::vector<std::string> &input, const int max) {
    return day15::calculateTuningFrequency(input, max);
}

int main(int argc, char **argv) {
    try {
        const auto filename = common::getFilename(argc, argv);
        const auto line = common::getNumber(argc, argv, 2);
        const auto max = common::getNumber(argc, argv, 3);
        const auto input = common::readInput(filename);
        std::cout << part1(input, line) << std::endl;
        std::cout << part2(input, max) << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}