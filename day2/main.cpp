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

unsigned part1(const std::vector<std::string> &input) {
    ShapeMapping enemyMapping{{'A', Shape::Rock}, {'B', Shape::Paper}, {'C', Shape::Scissors}};
    ShapeMapping ownMapping{{'X', Shape::Rock}, {'Y', Shape::Paper}, {'Z', Shape::Scissors}};

    unsigned score{0};

    for (const auto &line : input) {
        auto enemyShape = enemyMapping.at(line[0]);
        auto ownShape = ownMapping.at(line[2]);
        score += calculateRound(enemyShape, ownShape);
    }

    return score;
}

unsigned part2(const std::vector<std::string> &input) {
    ShapeMapping enemyMapping{{'A', Shape::Rock}, {'B', Shape::Paper}, {'C', Shape::Scissors}};

    std::map<Shape, Shape> winConditions = {{Shape::Rock, Shape::Paper},
                                            {Shape::Scissors, Shape::Rock},
                                            {Shape::Paper, Shape::Scissors}};
    std::map<Shape, Shape> lostConditions = {{Shape::Rock, Shape::Scissors},
                                             {Shape::Scissors, Shape::Paper},
                                             {Shape::Paper, Shape::Rock}};

    unsigned score{0};

    for (const auto &line : input) {
        const auto enemyShape = enemyMapping.at(line[0]);
        const auto ownChoice = line[2];

        if (ownChoice == 'Y') {  // drawn
            score += calculateRound(enemyShape, enemyShape);
        } else if (ownChoice == 'X') {  // lost
            const auto ownShape = lostConditions.at(enemyShape);
            score += calculateRound(enemyShape, ownShape);
        } else {  // win
            const auto ownShape = winConditions.at(enemyShape);
            score += calculateRound(enemyShape, ownShape);
        }
    }

    return score;
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