#include "day13.h"

#include <ctype.h>

#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>

namespace day13 {

unsigned countValidPairs(const std::vector<std::string>& input) {
    unsigned pairIndex{1};
    unsigned result{0};

    for (auto it = input.begin(); it != input.end(); ++it) {
        if (it->empty()) {
            pairIndex++;
            continue;
        }

        try {
            if (areInValidOrder(*it, *(it + 1))) {
                result += pairIndex;
            }
        } catch (std::exception& e) {
            std::cerr << e.what() << " " << *it << " " << *(it + 1) << std::endl;
        }

        it++;
    }

    return result;
}

namespace {
bool compareLists(const Packet& leftPacket, const Packet& rightPacket) {
    auto leftIt = leftPacket.begin();
    auto rightIt = rightPacket.begin();

    while (leftIt != leftPacket.end() && rightIt != rightPacket.end()) {
        if (isNumber(*leftIt) && isNumber(*rightIt)) {
            auto leftNumber = getNumber(*(leftIt));
            auto rightNumber = getNumber(*(rightIt));

            if (leftNumber < rightNumber) return true;

            if (rightNumber < leftNumber) return false;
        } else if (isList(*leftIt) && isNumber(*rightIt)) {
            auto leftList = getList(*(leftIt));
            auto rightNumber = getNumber(*(rightIt));

            Packet rightList{rightNumber};

            if (compareLists(leftList, rightList)) return true;

            if (compareLists(rightList, leftList)) return false;
        } else if (isNumber(*leftIt) && isList(*rightIt)) {
            auto leftNumber = getNumber(*(leftIt));
            auto rightList = getList(*(rightIt));

            Packet leftList{leftNumber};

            if (compareLists(leftList, rightList)) return true;

            if (compareLists(rightList, leftList)) return false;
        } else {
            auto leftList = getList(*(leftIt));
            auto rightList = getList(*(rightIt));

            if (compareLists(leftList, rightList)) return true;

            if (compareLists(rightList, leftList)) return false;
        }

        leftIt++;
        rightIt++;
    }

    if (leftIt == leftPacket.end() && rightIt == rightPacket.end()) return true;

    return leftIt == leftPacket.end();
}
}  // namespace

bool areInValidOrder(const std::string& left, const std::string& right) {
    const auto& leftPacket = parsePacket(left);
    const auto& rightPacket = parsePacket(right);

    return compareLists(leftPacket, rightPacket);
}

std::vector<std::any> parsePacket(const std::string& packet) {
    std::stack<Packet> stack{};

    auto it = packet.begin();

    while (it != packet.end()) {
        auto c = *it;
        if (c == ',') {
            it++;
            continue;
        } else if (c == '[') {
            stack.push(Packet{});
        } else if (c == ']') {
            Packet topPacket = stack.top();
            stack.pop();

            if (!stack.empty()) {
                stack.top().push_back(topPacket);
            } else {
                return topPacket;
            }
        } else if (std::isdigit(c)) {
            if (c == '1' && (*(it + 1) == '0')) {
                stack.top().push_back(10u);
                it++;
            } else
                stack.top().push_back(static_cast<unsigned>(c - 48));
        } else {
            throw std::runtime_error{"Could not parse char " + std::to_string(c)};
        }

        it++;
    }

    return Packet{};
}

bool isNumber(const std::any& a) { return a.has_value() && a.type() == typeid(unsigned); }

bool isList(const std::any& a) { return a.has_value() && a.type() == typeid(Packet); }

unsigned getNumber(const std::any& a) { return std::any_cast<unsigned>(a); }

Packet getList(const std::any& a) { return std::any_cast<Packet>(a); }

unsigned putInValidOrder(const std::vector<std::string>& input) {
    std::vector<Packet> packets;

    for (const auto& line : input) {
        if (line.empty()) continue;

        auto packet = parsePacket(line);
        packets.push_back(packet);
    }

    packets.push_back(parsePacket("[[2]]"));
    packets.push_back(parsePacket("[[6]]"));

    std::sort(packets.begin(), packets.end(),
              [](const Packet& p1, const Packet& p2) { return compareLists(p1, p2); });

    auto it1 = std::find_if(packets.begin(), packets.end(), [](const Packet& p) {
        return p.size() == 1 && isList(p[0]) && getList(p[0]).size() == 1 &&
               isNumber(getList(p[0]).front()) && getNumber(getList(p[0]).front()) == 2;
    });

    auto it2 = std::find_if(packets.begin(), packets.end(), [](const Packet& p) {
        return p.size() == 1 && isList(p[0]) && getList(p[0]).size() == 1 &&
               isNumber(getList(p[0]).front()) && getNumber(getList(p[0]).front()) == 6;
    });

    if (it1 == packets.end() || it2 == packets.end())
        throw std::runtime_error{"Could not find additional packets!"};

    return (std::distance(packets.begin(), it1) + 1) * (std::distance(packets.begin(), it2) + 1);
}
}  // namespace day13