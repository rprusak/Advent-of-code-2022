#include <gtest/gtest.h>

#include "day5.h"

void testOrder(const day5::Order& order, unsigned quantity, unsigned source, unsigned direction) {
    ASSERT_EQ(order.quantity, quantity);
    ASSERT_EQ(order.source, source);
    ASSERT_EQ(order.direction, direction);
}

TEST(parse, onValidInput_corectlyParsesText) {
    std::vector<std::string> input{
        "    [D]    ",        "[N] [C]    ",        "[Z] [M] [P]",        "",
        "move 1 from 2 to 1", "move 3 from 1 to 3", "move 2 from 2 to 1", "move 1 from 1 to 2"};

    auto [stacks, orders] = day5::parseInput(input);

    ASSERT_EQ(stacks.size(), 3u);
    auto v = std::vector<char>{'N', 'Z'};
    ASSERT_EQ(stacks[0], v);
    v = std::vector<char>{'D', 'C', 'M'};
    ASSERT_EQ(stacks[1], v);
    v = std::vector<char>{'P'};
    ASSERT_EQ(stacks[2], v);

    ASSERT_EQ(orders.size(), 4u);
    testOrder(orders[0], 1, 2, 1);
    testOrder(orders[1], 3, 1, 3);
    testOrder(orders[2], 2, 2, 1);
    testOrder(orders[3], 1, 1, 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}