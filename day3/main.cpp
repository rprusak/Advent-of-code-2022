#include <cctype>
#include <iostream>
#include <set>

#include "common.h"

unsigned getPriority(const char c) {
    if (std::islower(c)) {
        return c - 96;
    } else if (std::isupper(c)) {
        return c - 64 + 26;
    }

    return 0;
}

unsigned part1(const std::vector<std::string> &input) {
    unsigned result{0};

    for (const auto &line : input) {
        std::set<char> v1{line.begin(), line.begin() + line.size() / 2};
        std::set<char> v2{line.begin() + line.size() / 2, line.end()};
        std::vector<char> intersection;

        std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                              std::back_inserter(intersection));

        result += getPriority(intersection.at(0));
    }

    return result;
}

unsigned part2(const std::vector<std::string> &input) {
    unsigned result{0};

    for (size_t i = 0; i < input.size(); i += 3) {
        std::set<char> v1{input[i].begin(), input[i].end()};
        std::set<char> v2{input[i + 1].begin(), input[i + 1].end()};
        std::set<char> v3{input[i + 2].begin(), input[i + 2].end()};

        std::vector<char> intersection1;
        std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                              std::back_inserter(intersection1));

        std::vector<char> intersection2;
        std::set_intersection(v1.begin(), v1.end(), v3.begin(), v3.end(),
                              std::back_inserter(intersection2));

        std::vector<char> finalIntersection;
        std::set_intersection(intersection1.begin(), intersection1.end(), intersection2.begin(),
                              intersection2.end(), std::back_inserter(finalIntersection));

        result += getPriority(finalIntersection.at(0));
    }

    return result;
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