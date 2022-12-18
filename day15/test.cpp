#include <gtest/gtest.h>

#include "day15.h"

TEST(day15, parseLine_parseSimpleLine) {
    const auto Entry = day15::parseLine("Sensor at x=14, y=17: closest beacon is at x=10, y=16");
    ASSERT_EQ(Entry.first.first, 14);
    ASSERT_EQ(Entry.first.second, 17);
    ASSERT_EQ(Entry.second.first, 10);
    ASSERT_EQ(Entry.second.second, 16);
}

TEST(day15, parseLine_parseSimpleLineWithNegativeNumbers) {
    const auto Entry =
        day15::parseLine("Sensor at x=-14, y=-17: closest beacon is at x=-10, y=-16");
    ASSERT_EQ(Entry.first.first, -14);
    ASSERT_EQ(Entry.first.second, -17);
    ASSERT_EQ(Entry.second.first, -10);
    ASSERT_EQ(Entry.second.second, -16);
}

TEST(day15, parseLine_parseComplexLine) {
    const auto Entry = day15::parseLine(
        "Sensor at x=3832823, y=3346266: closest beacon is at x=3839159, y=3421933");
    ASSERT_EQ(Entry.first.first, 3832823);
    ASSERT_EQ(Entry.first.second, 3346266);
    ASSERT_EQ(Entry.second.first, 3839159);
    ASSERT_EQ(Entry.second.second, 3421933);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}