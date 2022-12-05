#include "day5.h"

#include <regex>

namespace day5 {
std::pair<std::vector<Stack>, std::vector<Order>> parseInput(
    const std::vector<std::string>& input) {
    static const std::regex pattern{R"#(^move (\d+) from (\d+) to (\d+)$)#"};
    std::vector<Stack> stacks((input.front().size() + 1) / 4);
    std::vector<Order> orders;
    bool parsingStacks = true;

    for (const auto& line : input) {
        if (line.empty()) {
            parsingStacks = false;
            continue;
        }

        if (parsingStacks) {
            size_t i = 1;
            size_t stackIndex = 0;

            while (i <= line.size() - 1) {
                if (line[i] != ' ') stacks.at(stackIndex).push_back(line[i]);

                i += 4;
                stackIndex++;
            }
        } else {
            std::smatch matchResult;
            if (!std::regex_match(line, matchResult, pattern))
                throw std::runtime_error{"Could not parse line " + line};

            Order order;
            order.quantity = std::stoul(matchResult[1].str());
            order.source = std::stoul(matchResult[2].str());
            order.direction = std::stoul(matchResult[3].str());

            orders.push_back(order);
        }
    }

    return std::make_pair(stacks, orders);
}
std::string calculateTopCrates(std::vector<Stack>& stacks, const std::vector<Order>& orders) {
    for (const auto& order : orders) {
        for (unsigned i = 1; i <= order.quantity; i++) {
            auto crate = stacks.at(order.source - 1).front();
            stacks.at(order.source - 1).erase(stacks.at(order.source - 1).begin());
            stacks.at(order.direction - 1).emplace(stacks.at(order.direction - 1).begin(), crate);
        }
    }

    std::string result;

    for (const auto& stack : stacks) {
        result += stack.front();
    }

    return result;
}

std::string calculateTopCratesWithMultiplePick(std::vector<Stack>& stacks,
                                               const std::vector<Order>& orders) {
    for (const auto& order : orders) {
        std::reverse(stacks.at(order.source - 1).begin(),
                     stacks.at(order.source - 1).begin() + order.quantity);

        for (unsigned i = 1; i <= order.quantity; i++) {
            auto crate = stacks.at(order.source - 1).front();
            stacks.at(order.source - 1).erase(stacks.at(order.source - 1).begin());
            stacks.at(order.direction - 1).emplace(stacks.at(order.direction - 1).begin(), crate);
        }
    }

    std::string result;

    for (const auto& stack : stacks) {
        result += stack.front();
    }

    return result;
}

}  // namespace day5
