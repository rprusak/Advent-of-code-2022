#include <any>
#include <iostream>
#include <vector>

#include "common.h"
#include "day13.h"

unsigned part1(const std::vector<std::string> &input) { return day13::countValidPairs(input); }

unsigned part2(const std::vector<std::string> &input) { return day13::putInValidOrder(input); }

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