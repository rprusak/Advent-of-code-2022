#include "day9.h"

#include <iostream>
#include <regex>
#include <set>

namespace day9 {

Motions parseInput(const std::vector<std::string>& input) {
    static const std::regex PATTERN(R"#(^(\w) (\d+)$)#");
    Motions result;
    std::smatch matchResult;

    for (const auto& line : input) {
        if (!std::regex_match(line, matchResult, PATTERN))
            throw std::runtime_error{"Could not parse line: " + line};

        DIRECTION direction;

        if (matchResult[1].str() == "R")
            direction = DIRECTION::RIGHT;
        else if (matchResult[1].str() == "D")
            direction = DIRECTION::DOWN;
        else if (matchResult[1].str() == "U")
            direction = DIRECTION::UP;
        else if (matchResult[1].str() == "L")
            direction = DIRECTION::LEFT;

        const auto step = std::stoi(matchResult[2].str());

        result.emplace_back(direction, step);
    }

    return result;
}

unsigned xDiff(const Point& head, const Point& tail) { return std::abs(head.first - tail.first); }

unsigned yDiff(const Point& head, const Point& tail) { return std::abs(head.second - tail.second); }

bool areTouching(const Point& head, const Point& tail) {
    return std::max(xDiff(head, tail), yDiff(head, tail)) <= 1;
}

bool isAwayOnXAxis(const Point& head, const Point& tail) {
    return xDiff(head, tail) > 1 && yDiff(head, tail) == 0;
}

bool isAwayOnYAxis(const Point& head, const Point& tail) {
    return xDiff(head, tail) == 0 && yDiff(head, tail) > 1;
}

bool isDirectlyAway(const Point& head, const Point& tail) {
    return isAwayOnXAxis(head, tail) || isAwayOnYAxis(head, tail);
}

void moveHead(Point& head, DIRECTION direction) {
    switch (direction) {
        case DIRECTION::UP:
            head.second++;
            break;
        case DIRECTION::DOWN:
            head.second--;
            break;
        case DIRECTION::RIGHT:
            head.first++;
            break;
        case DIRECTION::LEFT:
            head.first--;
            break;
    }
}

void moveTailOnX(const Point& head, Point& tail) {
    if (head.first > tail.first)
        tail.first++;
    else
        tail.first--;
}

void moveTailOnY(const Point& head, Point& tail) {
    if (head.second > tail.second)
        tail.second++;
    else
        tail.second--;
}

unsigned calculateTailTravelLength(const Motions& motions) {
    Point head{0, 0};
    Point tail{0, 0};

    std::set<Point> tailPositions;
    tailPositions.insert(tail);

    for (const auto& motion : motions) {
        for (int i = 0; i < motion.second; i++) {
            moveHead(head, motion.first);

            if (areTouching(head, tail)) continue;

            if (isDirectlyAway(head, tail)) {
                if (isAwayOnXAxis(head, tail)) {
                    moveTailOnX(head, tail);
                } else {
                    moveTailOnY(head, tail);
                }
            } else {
                moveTailOnX(head, tail);
                moveTailOnY(head, tail);
            }

            tailPositions.insert(tail);
        }
    }

    return tailPositions.size();
}

unsigned calculateTailTravelLength2(const Motions& motions) {
    std::vector<Point> rope(10, {0, 0});

    std::set<Point> tailPositions;
    tailPositions.insert(rope.back());

    for (const auto& motion : motions) {
        for (int i = 0; i < motion.second; i++) {
            moveHead(rope.front(), motion.first);

            for (int j = 1; j < 10; j++) {
                const auto& previousKnot = rope[j - 1];
                auto& currentKnot = rope[j];

                if (areTouching(previousKnot, currentKnot)) break;

                if (isDirectlyAway(previousKnot, currentKnot)) {
                    if (isAwayOnXAxis(previousKnot, currentKnot)) {
                        moveTailOnX(previousKnot, currentKnot);
                    } else {
                        moveTailOnY(previousKnot, currentKnot);
                    }
                } else {
                    moveTailOnX(previousKnot, currentKnot);
                    moveTailOnY(previousKnot, currentKnot);
                }
            }

            tailPositions.insert(rope.back());
        }
    }

    return tailPositions.size();
}

}  // namespace day9