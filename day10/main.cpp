#include <array>
#include <iostream>
#include <set>

#include "common.h"

bool isMeasurmentCycle(int cycle) {
    const static std::set<int> measurmentCycles{20, 60, 100, 140, 180, 220};
    return measurmentCycles.contains(cycle);
}

bool isEndCycle(int cycle) { return cycle >= 220; }

unsigned part1(const std::vector<std::string>& input) {
    int cycle{1};
    int X{1};
    int score{0};

    for (const auto& line : input) {
        if (isMeasurmentCycle(cycle)) score += X * cycle;

        if (isEndCycle(cycle)) break;

        if (line == "noop") {
            cycle++;
            continue;
        }

        // addx
        const auto splitLine = common::split(line, " ");
        const auto value = std::stoi(splitLine.at(1));

        cycle++;

        if (isMeasurmentCycle(cycle)) score += X * cycle;

        cycle++;
        X += value;
    }

    return score;
}

using Crt = std::array<std::array<char, 40>, 6>;

void markCycle(Crt& crt, int cycle, int x) {
    if (cycle > 240) return;

    int row = (cycle - 1) / 40;
    int cell = (cycle - 1) % 40;

    if (cell >= x - 1 && cell <= x + 1)
        crt[row][cell] = '#';
    else
        crt[row][cell] = '.';
}

void drawCrt(Crt& crt) {
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 40; i++) {
            std::cout << crt[j][i];
        }
        std::cout << std::endl;
    }
}

void part2(const std::vector<std::string>& input) {
    int cycle{1};
    int X{1};

    Crt crt;

    for (const auto& line : input) {
        markCycle(crt, cycle, X);

        if (cycle >= 240) break;

        if (line == "noop") {
            cycle++;
            continue;
        }

        // addx
        const auto splitLine = common::split(line, " ");
        const auto value = std::stoi(splitLine.at(1));

        cycle++;
        markCycle(crt, cycle, X);

        cycle++;
        X += value;
    }

    drawCrt(crt);
}

int main(int argc, char** argv) {
    try {
        const auto filename = common::getFilename(argc, argv);
        const auto input = common::readInput(filename);
        std::cout << part1(input) << std::endl;
        part2(input);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}