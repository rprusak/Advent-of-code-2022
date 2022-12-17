#ifndef STARTER_DAY14_H
#define STARTER_DAY14_H

#include <set>
#include <string>
#include <utility>
#include <vector>

namespace day14 {

class Point : public std::pair<unsigned, unsigned> {
public:
    using std::pair<unsigned, unsigned>::pair;

    enum class Type { UNKNOWN, ROCK, SAND };

    void setType(Type type) { _type = type; }

    char draw() const {
        switch (_type) {
            case Type::UNKNOWN:
                return 'X';
            case Type::ROCK:
                return '#';
            case Type::SAND:
                return 'o';
        }

        return ' ';
    }

private:
    Type _type{Type::UNKNOWN};
};

std::set<Point> createRocks(const std::vector<std::string>& input);

unsigned countSandBeforeFalling(const std::vector<std::string>& input);

}  // namespace day14

#endif  // STARTER_DAY14_H