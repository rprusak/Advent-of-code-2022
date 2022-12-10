#include <iostream>
#include <vector>

#include "common.h"

void markEdges(std::vector<std::vector<bool>> &visibleTrees) {
    const unsigned height = visibleTrees.size();
    const unsigned width = visibleTrees.front().size();

    for (unsigned i = 0; i < width; i++) {
        visibleTrees[0][i] = true;
        visibleTrees[height - 1][i] = true;
    }

    for (unsigned i = 0; i < height; i++) {
        visibleTrees[i][0] = true;
        visibleTrees[i][width - 1] = true;
    }
}

unsigned countVisibleTrees(std::vector<std::vector<bool>> &visibleTrees) {
    unsigned result{0};

    for (const auto &row : visibleTrees) {
        for (const auto value : row) {
            if (value) result++;
        }
    }

    return result;
}

std::vector<std::vector<unsigned>> convertToNumbers(const std::vector<std::string> &input) {
    const unsigned height = input.size();
    const unsigned width = input.front().size();

    std::vector<std::vector<unsigned>> trees(height, std::vector<unsigned>(width, 0));

    for (unsigned row = 0; row < height; row++) {
        for (unsigned column = 0; column < width; column++) {
            trees[row][column] = input[row][column] - 48;
        }
    }

    return trees;
}

void markVisibleTrees(const std::vector<std::vector<unsigned>> &trees,
                      std::vector<std::vector<bool>> &visibleTrees) {
    const unsigned height = trees.size();
    const unsigned width = trees.front().size();

    // left to right
    for (unsigned row = 1; row < height - 1; row++) {
        unsigned highestTree = trees[row][0];
        for (unsigned column = 1; column < width - 1; column++) {
            if (trees[row][column] > highestTree) {
                visibleTrees[row][column] = true;
                highestTree = trees[row][column];
            }
        }
    }

    // right to left
    for (unsigned row = 1; row < height - 1; row++) {
        unsigned highestTree = trees[row][width - 1];
        for (unsigned column = width - 2; column >= 1; column--) {
            if (trees[row][column] > highestTree) {
                visibleTrees[row][column] = true;
                highestTree = trees[row][column];
            }
        }
    }

    // top to bottom
    for (unsigned column = 1; column < width - 1; column++) {
        unsigned highestTree = trees[0][column];
        for (unsigned row = 1; row < height - 1; row++) {
            if (trees[row][column] > highestTree) {
                visibleTrees[row][column] = true;
                highestTree = trees[row][column];
            }
        }
    }

    // bottom to top
    for (unsigned column = 1; column < width - 1; column++) {
        unsigned highestTree = trees[height - 1][column];
        for (unsigned row = height - 2; row >= 1; row--) {
            if (trees[row][column] > highestTree) {
                visibleTrees[row][column] = true;
                highestTree = trees[row][column];
            }
        }
    }
}

unsigned calculateVisibleTreesCount(const std::vector<std::vector<unsigned>> &trees) {
    const unsigned height = trees.size();
    const unsigned width = trees.front().size();

    std::vector<std::vector<bool>> visibleTrees(height, std::vector(width, false));
    markEdges(visibleTrees);
    markVisibleTrees(trees, visibleTrees);

    return countVisibleTrees(visibleTrees);
}

unsigned part1(const std::vector<std::string> &input) {
    const auto trees = convertToNumbers(input);
    return calculateVisibleTreesCount(trees);
}

enum class DIRECTION { UP, DOWN, LEFT, RIGHT };

unsigned calculateVisibleTreesInDirection(const std::vector<std::vector<unsigned>> &trees,
                                          unsigned y, unsigned x, DIRECTION direction) {
    const unsigned height = trees.size();
    const unsigned width = trees.front().size();
    const unsigned startTreeHeight = trees[y][x];

    bool isVertical = (direction == DIRECTION::DOWN) || (direction == DIRECTION::UP);
    bool isIncreasing = (direction == DIRECTION::DOWN) || (direction == DIRECTION::RIGHT);

    unsigned begin = isVertical ? y : x;
    unsigned end = isVertical ? (isIncreasing ? height - 1 : 0) : (isIncreasing ? width - 1 : 0);

    if (begin == end) return 0;

    unsigned highestTree = 0;
    unsigned score = 0;

    while (true) {
        begin += isIncreasing ? +1 : -1;

        const auto newTree = trees[isVertical ? begin : y][isVertical ? x : begin];
        score++;

        if (newTree > highestTree) highestTree = newTree;

        if (highestTree >= startTreeHeight) break;

        if (begin == end) break;
    }

    return score;
}

unsigned calculateTreeScore(const std::vector<std::vector<unsigned>> &trees, unsigned y,
                            unsigned x) {
    const auto leftCount = calculateVisibleTreesInDirection(trees, y, x, DIRECTION::LEFT);
    const auto rightCount = calculateVisibleTreesInDirection(trees, y, x, DIRECTION::RIGHT);
    const auto downCount = calculateVisibleTreesInDirection(trees, y, x, DIRECTION::DOWN);
    const auto upCount = calculateVisibleTreesInDirection(trees, y, x, DIRECTION::UP);

    return leftCount * rightCount * downCount * upCount;
}

unsigned part2(const std::vector<std::string> &input) {
    const unsigned height = input.size();
    const unsigned width = input.front().size();

    const auto trees = convertToNumbers(input);

    unsigned bestTreeScore{0};

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            const auto score = calculateTreeScore(trees, y, x);
            bestTreeScore = std::max(bestTreeScore, score);
        }
    }

    return bestTreeScore;
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