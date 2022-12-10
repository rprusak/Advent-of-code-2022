#include <iostream>
#include <map>

#include "common.h"
#include "day9.h"

unsigned part1(const std::vector<std::string> &input) {
    const auto motions = day9::parseInput(input);
    return calculateTailTravelLength(motions);
}

unsigned part2(const std::vector<std::string> &input) {
    const auto motions = day9::parseInput(input);
    return calculateTailTravelLength2(motions);
}

int main(int argc, char **argv) {
    try {
        const auto filename = common::getFilename(argc, argv);
        const auto input = common::readInput(filename);
        std::cout << part1(input) << std::endl;
        std::cout << part2(input) << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}