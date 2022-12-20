#include <gtest/gtest.h>

#include "day16.h"

TEST(day16, parseLine) {
    const auto output =
        day16::parseLine("Valve AA has flow rate=15; tunnels lead to valves DD, II, BB");
    ASSERT_EQ(output.first, "AA");

    ASSERT_EQ(output.second.first, 15u);
    ASSERT_EQ(output.second.second.size(), 3u);
    ASSERT_EQ(output.second.second[0], "DD");
    ASSERT_EQ(output.second.second[1], "II");
    ASSERT_EQ(output.second.second[2], "BB");
}

TEST(day16, parseLine2) {
    const auto output = day16::parseLine("Valve JJ has flow rate=0; tunnel leads to valve II");
    ASSERT_EQ(output.first, "JJ");

    ASSERT_EQ(output.second.first, 0u);
    ASSERT_EQ(output.second.second.size(), 1u);
    ASSERT_EQ(output.second.second[0], "II");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}