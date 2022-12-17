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

namespace {
void display(const std::set<Point>& rocks, const Point& current, bool displayPoint = false) {
    return;

    static unsigned counter{0};
    system("clear");

    if (!displayPoint) counter++;
    std::cout << counter << std::endl;

    auto xMin = rocks.begin()->first;
    auto xMax = rocks.begin()->first;
    auto yMin = 0u;
    auto yMax = rocks.begin()->second;

    for (const auto& p : rocks) {
        xMin = std::min(p.first, xMin);
        xMax = std::max(p.first, xMax);
        yMin = std::min(p.second, yMin);
        yMax = std::max(p.second, yMax);
    }

    if (xMin != 0) xMin -= 1;

    if (yMin != 0) yMin -= 1;

    xMax += 1;
    yMax += 1;

    for (auto y = yMin; y <= yMax; y++) {
        for (auto x = xMin; x <= xMax; x++) {
            if (rocks.contains(Point{x, y})) {
                const auto p = rocks.find(Point{x, y});
                std::cout << p->draw();
            } else if (displayPoint && x == current.first && y == current.second)
                std::cout << "$";
            else {
                if (x == 500 && y == 0)
                    std::cout << "+";
                else
                    std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds{200});
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

bool canGoLeft(const Point& newPoint, const std::set<Point>& currentPoints) {
    return !currentPoints.contains(Point{newPoint.first - 1, newPoint.second + 1});
}

bool canGoRight(const Point& newPoint, const std::set<Point>& currentPoints) {
    return !currentPoints.contains(Point{newPoint.first + 1, newPoint.second + 1});
}
}  // namespace

unsigned countSandBeforeFalling(const std::vector<std::string>& input) {
    auto points = createRocks(input);

    Point p{500, 0};
    p.setType(Point::Type::SAND);
    unsigned counter{0};

    while (true) {
        if (!points.contains(Point{p.first, p.second + 1})) {
            auto val = findBottomPoint(p, points);
            if (!val) {
                points.insert(p);
                display(points, {});
                break;
            }

            p.second = val.value() - 1;
        }

        if (canGoLeft(p, points)) {
            p.first -= 1;
            p.second += 1;
            display(points, p, true);
            continue;
        }

        if (canGoRight(p, points)) {
            p.first += 1;
            p.second += 1;
            display(points, p, true);
            continue;
        }

        points.insert(p);

        display(points, {});

        p = Point{500, 0};
        p.setType(Point::Type::SAND);
        counter++;
    }

    return counter;
}
}  // namespace day14
