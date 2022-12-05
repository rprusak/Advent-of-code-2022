#include <iostream>

#include "common.h"
#include "day5.h"

std::string part1(const std::vector<std::string> &input) {
    auto [stacks, orders] = day5::parseInput(input);
    return day5::calculateTopCrates(stacks, orders);
}

std::string part2(const std::vector<std::string> &input) {
    auto [stacks, orders] = day5::parseInput(input);
    return day5::calculateTopCratesWithMultiplePick(stacks, orders);
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