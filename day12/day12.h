#ifndef STARTER_DAY12_H
#define STARTER_DAY12_H

#include <map>
#include <string>
#include <vector>

namespace day12 {

using Point = std::pair<unsigned, unsigned>;

class BFSSolver {
public:
    BFSSolver(const std::vector<std::string>& input)
        : _input{input},
          _inputHeight{static_cast<unsigned int>(input.size())},
          _inputWidth{static_cast<unsigned int>(input.front().size())} {}

    unsigned findPathLength(const Point startPoint, const Point endPoint);

private:
    enum class Status { NEW, VISITED, DONE };

    bool isNew(const Point& point);
    void setStatus(const Point& point, Status status);

    unsigned getDistance(const Point& point);
    void setDistance(const Point& point, unsigned val);

    unsigned getPointHeight(char value);
    std::vector<Point> getNearPoints(const Point& point);

    std::map<Point, Status> _pointsStatus;
    std::map<Point, unsigned> _pointsDistance;

    const std::vector<std::string>& _input;
    const unsigned _inputHeight;
    const unsigned _inputWidth;
};

Point findStartPointLocation(const std::vector<std::string>& input);
Point findEndPointLocation(const std::vector<std::string>& input);
unsigned getShortestPathLengthFromStart(const std::vector<std::string>& input);
unsigned getShortestPathLengthFromAny(const std::vector<std::string>& input);
}  // namespace day12

#endif  // STARTER_DAY12_H
