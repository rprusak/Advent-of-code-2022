#ifndef STARTER_DAY5_H
#define STARTER_DAY5_H

#include <stack>
#include <string>
#include <vector>

namespace day5 {

using Stack = std::vector<char>;

struct Order {
    unsigned quantity{0};
    unsigned source{0};
    unsigned direction{0};
};

std::pair<std::vector<Stack>, std::vector<Order>> parseInput(const std::vector<std::string>& input);
std::string calculateTopCrates(std::vector<Stack>& stacks, const std::vector<Order>& orders);
std::string calculateTopCratesWithMultiplePick(std::vector<Stack>& stacks,
                                               const std::vector<Order>& orders);
}  // namespace day5

#endif  // STARTER_DAY5_H
