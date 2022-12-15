#include "day12.h"

#include <iostream>
#include <numeric>
#include <queue>

namespace day12 {

unsigned getShortestPathLengthFromStart(const std::vector<std::string>& input) {
    const auto start = findStartPointLocation(input);
    const auto end = findEndPointLocation(input);

    BFSSolver solver{input};

    return solver.findPathLength(start, end);
}

Point findStartPointLocation(const std::vector<std::string>& input) {
    for (unsigned y = 0; y < input.size(); y++) {
        for (unsigned x = 0; x < input[y].size(); x++) {
            if (input[y][x] == 'S') return Point{x, y};
        }
    }

    return Point{0, 0};
}

Point findEndPointLocation(const std::vector<std::string>& input) {
    for (unsigned y = 0; y < input.size(); y++) {
        for (unsigned x = 0; x < input[y].size(); x++) {
            if (input[y][x] == 'E') return Point{x, y};
        }
    }

    return Point{0, 0};
}
unsigned getShortestPathLengthFromAny(const std::vector<std::string>& input) {
    unsigned shortest{std::numeric_limits<unsigned>::max()};
    const auto end = findEndPointLocation(input);

    for (unsigned y = 0; y < input.size(); y++) {
        for (unsigned x = 0; x < input[y].size(); x++) {
            if (input[y][x] == 'a') {
                BFSSolver solver{input};
                Point start{x, y};

                try {
                    const auto result = solver.findPathLength(start, end);

                    if (result < shortest) shortest = result;
                } catch (std::exception& e) {
                    // kekw
                    // std::cerr << e.what() << std::endl;
                }
            }
        }
    }

    return shortest;
}

unsigned BFSSolver::findPathLength(const Point startPoint, const Point endPoint) {
    setStatus(startPoint, Status::VISITED);
    setDistance(startPoint, 0);

    std::queue<Point> pointsQueue;
    pointsQueue.push(startPoint);

    while (!pointsQueue.empty()) {
        const Point p = pointsQueue.front();
        pointsQueue.pop();

        const auto nearPoints = getNearPoints(p);
        for (const auto& nearPoint : nearPoints) {
            if (isNew(nearPoint)) {
                setStatus(nearPoint, Status::VISITED);
                setDistance(nearPoint, getDistance(p) + 1);
                pointsQueue.push(nearPoint);
            }
        }

        setStatus(p, Status::DONE);
    }

    return _pointsDistance.at(endPoint);
}

bool BFSSolver::isNew(const day12::Point& point) { return _pointsStatus[point] == Status::NEW; }

void BFSSolver::setStatus(const Point& point, Status status) { _pointsStatus[point] = status; }

unsigned BFSSolver::getDistance(const Point& point) { return _pointsDistance[point]; }

void BFSSolver::setDistance(const day12::Point& point, unsigned int val) {
    _pointsDistance[point] = val;
}

unsigned BFSSolver::getPointHeight(char value) {
    if (value == 'S')
        value = 'a';
    else if (value == 'E')
        value = 'z';

    return value - 96;
}

std::vector<Point> BFSSolver::getNearPoints(const day12::Point& point) {
    std::vector<Point> possiblePoints;

    auto isAllowed = [&](const Point& newPoint) {
        auto currentHeight = getPointHeight(_input[point.second][point.first]);
        auto newHeight = getPointHeight(_input[newPoint.second][newPoint.first]);

        if (newHeight > currentHeight) return newHeight - currentHeight <= 1;

        return true;
        // return std::abs(int(currentHeight - newHeight)) <= 1;
    };

    if (point.first != 0) {
        Point newPoint{point.first - 1, point.second};
        if (isAllowed(newPoint)) possiblePoints.push_back(newPoint);
    }

    if (point.second != 0) {
        Point newPoint{point.first, point.second - 1};
        if (isAllowed(newPoint)) possiblePoints.push_back(newPoint);
    }

    if (point.first != _inputWidth - 1) {
        Point newPoint{point.first + 1, point.second};
        if (isAllowed(newPoint)) possiblePoints.push_back(newPoint);
    }

    if (point.second != _inputHeight - 1) {
        Point newPoint{point.first, point.second + 1};
        if (isAllowed(newPoint)) possiblePoints.push_back(newPoint);
    }

    return possiblePoints;
}

}  // namespace day12