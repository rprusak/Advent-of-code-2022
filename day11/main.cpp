#include <iostream>
#include <map>

#include "common.h"
#include "day11.h"

uint64_t part1(const std::vector<std::string> &input) {
    auto monkeys = day11::parseInput(input);
    return day11::performInspections(monkeys);
}

uint64_t part2(const std::vector<std::string> &input) {
    auto monkeys = day11::parseInput(input);
    return day11::performInspections(monkeys, 10000, false);
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