#include "day15.h"

#include <iomanip>
#include <iostream>
#include <map>
#include <optional>
#include <regex>
#include <set>

namespace day15 {

int64_t calculateDistance(const Point& a, const Point& b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

unsigned countPositionsWithoutBeaconInLine(const std::vector<std::string>& input,
                                           const int64_t line) {
    const auto entries = parseInput(input);

    std::set<Point> points;
    for (const auto& entry : entries) {
        const auto& sensor = entry.first;
        const auto& beacon = entry.second;

        auto distance = calculateDistance(sensor, beacon);

        if (distance == 0) continue;

        Point currentPoint{sensor.first, line};

        if (calculateDistance(currentPoint, sensor) > distance) continue;

        // go left
        while (calculateDistance(currentPoint, sensor) <= distance) {
            if (currentPoint != sensor && currentPoint != beacon) points.insert(currentPoint);

            currentPoint.first--;
        }

        // gor right
        currentPoint.first = sensor.first + 1;
        while (calculateDistance(currentPoint, sensor) <= distance) {
            if (currentPoint != sensor && currentPoint != beacon) points.insert(currentPoint);

            currentPoint.first++;
        }
    }

    return points.size();
}

Entry parseLine(const std::string& line) {
    static const std::regex pattern{
        R"#(^Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+)$)#"};

    std::smatch matchResult;
    if (!std::regex_match(line, matchResult, pattern))
        throw std::runtime_error{"Could not parse line " + line};

    int64_t sensorX = std::stoi(matchResult[1].str());
    int64_t sensorY = std::stoi(matchResult[2].str());
    int64_t beaconX = std::stoi(matchResult[3].str());
    int64_t beaconY = std::stoi(matchResult[4].str());

    return Entry{Point{sensorX, sensorY}, Point{beaconX, beaconY}};
}

std::vector<Entry> parseInput(const std::vector<std::string>& input) {
    std::vector<Entry> entries;

    for (const auto& line : input) entries.push_back(parseLine(line));

    return entries;
}

uint64_t calculateTuningFrequency(const std::vector<std::string>& input, const int64_t max) {
    const auto entries = parseInput(input);

    for (int64_t line = 0; line <= max; line++) {
        std::set<std::pair<int64_t, int64_t>> lineCoverage;

        for (const auto& entry : entries) {
            const auto& sensor = entry.first;
            const auto& beacon = entry.second;

            auto sensor2BeaconDistance = calculateDistance(sensor, beacon);

            int64_t yDistance = std::abs(sensor.second - line);

            if (yDistance > sensor2BeaconDistance) continue;

            int64_t xDistance = sensor2BeaconDistance - yDistance;

            int64_t xBegin = sensor.first - xDistance;
            int64_t xEnd = sensor.first + xDistance;

            if (xEnd < 0) continue;

            if (xBegin > max) continue;

            if (xBegin < 0) xBegin = 0;

            if (xEnd > max) xEnd = max;

            lineCoverage.emplace(xBegin, xEnd);
        }

        auto it = lineCoverage.begin();
        auto firstRange = *it;
        it++;

        while (it != lineCoverage.end()) {
            auto nextRange = *it;

            bool cantBeMerged = (nextRange.first > firstRange.second + 1);

            if (cantBeMerged) {
                std::cout << "Cant merge line " << line << std::endl;
                std::cout << firstRange.second + 1 << " * 4000000 + " << line << std::endl;
                return ((uint64_t)firstRange.second + 1) * (uint64_t)4000000 + (uint64_t)line;
            }
            firstRange.first = std::min(firstRange.first, nextRange.first);
            firstRange.second = std::max(firstRange.second, nextRange.second);
            it++;
        }

        if (!(firstRange.first == 0 && firstRange.second == max)) {
            std::cout << "Cant cover line " << line << std::endl;
        }
    }

    return 0;
}

}  // namespace day15