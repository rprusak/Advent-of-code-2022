#include <iostream>
#include <map>

#include "common.h"

enum class Shape { Rock, Paper, Scissors };

using ShapeMapping = std::map<char, Shape>;

const std::map<Shape, unsigned> SCORE{{Shape::Scissors, 3}, {Shape::Rock, 1}, {Shape::Paper, 2}};

unsigned calculateRound(const Shape enemyShape, const Shape ownShape) {
    unsigned roundScore{0};

    auto isWin = [](const Shape enemyShape, const Shape ownShape) {
        return (enemyShape == Shape::Scissors && ownShape == Shape::Rock) ||
               (enemyShape == Shape::Rock && ownShape == Shape::Paper) ||
               (enemyShape == Shape::Paper && ownShape == Shape::Scissors);
    };

    if (enemyShape == ownShape) {
        roundScore += 3;
    } else if (isWin(enemyShape, ownShape)) {
        roundScore += 6;
    } else {
        roundScore += 0;
    }

    return SCORE.at(ownShape) + roundScore;
}

unsigned part1(const std::vector<std::string> &input) { return 0; }

unsigned part2(const std::vector<std::string> &input) { return 0; }

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