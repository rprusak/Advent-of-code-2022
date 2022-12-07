#include <gtest/gtest.h>

#include "day6.h"

TEST(day6, getFirstStartOfPacketMarker) {
    ASSERT_EQ(day6::getFirstStartOfPacketMarker("mjqjpqmgbljsphdztnvjfqwrcgsmlb"), 7u);
    ASSERT_EQ(day6::getFirstStartOfPacketMarker("bvwbjplbgvbhsrlpgdmjqwftvncz"), 5u);
    ASSERT_EQ(day6::getFirstStartOfPacketMarker("nppdvjthqldpwncqszvftbrmjlhg"), 6u);
    ASSERT_EQ(day6::getFirstStartOfPacketMarker("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg"), 10u);
    ASSERT_EQ(day6::getFirstStartOfPacketMarker("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"), 11u);
}

TEST(day6, getFirstBigStartOfPacketMarker) {
    ASSERT_EQ(day6::getFirstBigStartOfPacketMarker("mjqjpqmgbljsphdztnvjfqwrcgsmlb"), 19u);
    ASSERT_EQ(day6::getFirstBigStartOfPacketMarker("bvwbjplbgvbhsrlpgdmjqwftvncz"), 23u);
    ASSERT_EQ(day6::getFirstBigStartOfPacketMarker("nppdvjthqldpwncqszvftbrmjlhg"), 23u);
    ASSERT_EQ(day6::getFirstBigStartOfPacketMarker("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg"), 29u);
    ASSERT_EQ(day6::getFirstBigStartOfPacketMarker("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"), 26u);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}