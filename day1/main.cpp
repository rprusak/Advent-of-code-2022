#include <iostream>
#include <queue>
#include <set>
#include <numeric>
#include "common.h"

unsigned part1(const std::vector<std::string> &caloriesList) {
    unsigned currentCalories{0};
    unsigned bestCalories{0};


    for (const auto &calories: caloriesList) {
        if (!calories.empty()) {
            currentCalories += std::stoul(calories);
        } else {
            if (bestCalories < currentCalories)
                bestCalories = currentCalories;
            currentCalories = 0;
        }
    }

    return bestCalories;
}

unsigned part2(const std::vector<std::string> &caloriesList) {
    unsigned currentCalories{0};
    std::set<unsigned> bestThree;

    auto addCalories = [&bestThree](unsigned calories) {
        if (bestThree.size() < 3) {
            bestThree.insert(calories);
        } else {
            if (calories > *bestThree.begin()) {
                bestThree.erase(bestThree.begin());
                bestThree.insert(calories);
            }
        }
    };

    for (const auto &calories: caloriesList) {
        if (!calories.empty()) {
            currentCalories += std::stoul(calories);
        } else {
            addCalories(currentCalories);
            currentCalories = 0;
        }
    }

    if (currentCalories != 0)
        addCalories(currentCalories);

    return std::accumulate(bestThree.begin(), bestThree.end(), 0);
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