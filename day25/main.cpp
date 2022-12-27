#include <iostream>
#include <map>

#include "common.h"
#include "day25.h"

std::string part1(const std::vector<std::string> &input) {
    const auto sum = day25::calculateSumOfSNAFUNumbers(input);
    return day25::convertToSNAFU(sum);
}

int main(int argc, char **argv) {
    try {
        const auto filename = common::getFilename(argc, argv);
        const auto input = common::readInput(filename);
        std::cout << "part 1: " << part1(input) << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}