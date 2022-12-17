#include "day14.h"

#include <iostream>
#include <optional>
#include <thread>

#include "common.h"

namespace day14 {
std::set<Point> createRocks(const std::vector<std::string>& input) {
    std::set<Point> rocks;

    for (const auto& line : input) {
        std::vector<Point> parsedPoints;

        const auto split = common::split(line, "->");

        for (const auto& splitPoint : split) {
            const auto coordiantes = common::split(common::trim(splitPoint), ",");
            unsigned x = std::stoul(coordiantes[0]);
            unsigned y = std::stoul(coordiantes[1]);

            parsedPoints.emplace_back(x, y);
        }

        for (size_t i = 0; i < parsedPoints.size() - 1; i++) {
            auto xStart = std::min(parsedPoints[i].first, parsedPoints[i + 1].first);
            auto xEnd = std::max(parsedPoints[i].first, parsedPoints[i + 1].first);
            auto yStart = std::min(parsedPoints[i].second, parsedPoints[i + 1].second);
            auto yEnd = std::max(parsedPoints[i].second, parsedPoints[i + 1].second);

            for (auto x = xStart; x <= xEnd; x++) {
                for (auto y = yStart; y <= yEnd; y++) {
                    Point p{x, y};
                    p.setType(Point::Type::ROCK);
                    rocks.emplace(p);
                }
            }
        }
    }

    return rocks;
}

void addFloor(std::set<Point>& rocks) {
    auto xMin = rocks.begin()->first;
    auto xMax = rocks.begin()->first;
    auto yMax = rocks.begin()->second;

    for (const auto& p : rocks) {
        xMin = std::min(p.first, xMin);
        xMax = std::max(p.first, xMax);
        yMax = std::max(p.second, yMax);
    }

    xMax += 500;
    xMin = 0;
    yMax += 2;

    for (auto x = xMin; x <= xMax; x++) {
        Point p{x, yMax};
        p.setType(Point::Type::ROCK);
        rocks.insert(p);
    }
}

std::optional<unsigned> findBottomPoint(const Point& newPoint,
                                        const std::set<Point>& currentPoints) {
    std::optional<unsigned> result;

    auto pointInSameColumn = [&newPoint](const Point& p) {
        return newPoint.first == p.first && p.second > newPoint.second;
    };

    auto it = std::find_if(currentPoints.begin(), currentPoints.end(), pointInSameColumn);

    while (it != currentPoints.end()) {
        if (!result.has_value())
            result = it->second;
        else {
            if (it->second < result.value()) result = it->second;
        }

        it = std::find_if(++it, currentPoints.end(), pointInSameColumn);
    }

    return result;
}

Point createStartPoint() {
    Point p{500, 0};
    p.setType(Point::Type::SAND);
    return p;
}

bool canGoLeft(const Point& newPoint, const std::set<Point>& currentPoints) {
    return !currentPoints.contains(Point{newPoint.first - 1, newPoint.second + 1});
}

bool canGoRight(const Point& newPoint, const std::set<Point>& currentPoints) {
    return !currentPoints.contains(Point{newPoint.first + 1, newPoint.second + 1});
}

bool canMoveDown(const Point& newPoint, const std::set<Point>& currentPoints) {
    return !currentPoints.contains(Point{newPoint.first, newPoint.second + 1});
}

bool isMoveable(const Point& newPoint, const std::set<Point>& currentPoints) {
    return canMoveDown(newPoint, currentPoints) || canGoLeft(newPoint, currentPoints) ||
           canGoRight(newPoint, currentPoints);
}

void goLeft(Point& p) {
    p.first -= 1;
    p.second += 1;
}

void goRight(Point& p) {
    p.first += 1;
    p.second += 1;
}

unsigned countSandBeforeFalling(const std::vector<std::string>& input) {
    auto points = createRocks(input);

    Point p = createStartPoint();
    unsigned counter{0};

    while (true) {
        if (canMoveDown(p, points)) {
            auto val = findBottomPoint(p, points);
            if (!val) break;

            p.second = val.value() - 1;
        }

        if (canGoLeft(p, points)) {
            goLeft(p);
            continue;
        }

        if (canGoRight(p, points)) {
            goRight(p);
            continue;
        }

        points.insert(p);

        p = createStartPoint();
        counter++;
    }

    return counter;
}

unsigned countSandBeforeStoppingOnFloor(const std::vector<std::string>& input) {
    auto points = createRocks(input);
    addFloor(points);

    Point p = createStartPoint();
    unsigned counter{0};

    while (true) {
        if (canMoveDown(p, points)) {
            auto val = findBottomPoint(p, points);
            if (!val) {
                points.insert(p);
                break;
            }

            p.second = val.value() - 1;
        }

        if (canGoLeft(p, points)) {
            goLeft(p);
            continue;
        }

        if (canGoRight(p, points)) {
            goRight(p);
            continue;
        }

        points.insert(p);

        p = createStartPoint();
        counter++;

        if (!isMoveable(p, points)) break;
    }

    return counter + 1;
}
}  // namespace day14
