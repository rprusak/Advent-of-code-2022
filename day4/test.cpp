#include <gtest/gtest.h>

#include "day4.h"

TEST(parseLine, onValidString_parsesInput) {
    auto entry = day4::parseLine("2-4,6-8");

    ASSERT_EQ(entry.first.first, 2u);
    ASSERT_EQ(entry.first.second, 4u);
    ASSERT_EQ(entry.second.first, 6u);
    ASSERT_EQ(entry.second.second, 8u);

    entry = day4::parseLine("35-39,35-83");

    ASSERT_EQ(entry.first.first, 35u);
    ASSERT_EQ(entry.first.second, 39u);
    ASSERT_EQ(entry.second.first, 35u);
    ASSERT_EQ(entry.second.second, 83u);
}

TEST(parseLine, onInvalidString_throwsException) {
    ASSERT_THROW(day4::parseLine("2-4,6-"), std::runtime_error);
}

TEST(Range, containsRange_onContainedRange_returnsTrue) {
    day4::Range first{2, 8};
    day4::Range second{3, 7};

    ASSERT_TRUE(first.containsRange(second));
}

TEST(Range, containsRange_onNonContainedRange_returnsFalse) {
    day4::Range first{2, 8};
    day4::Range second{3, 15};

    ASSERT_FALSE(first.containsRange(second));
}

TEST(Range, overlapRange_onOverlappedRange_retrunsTrue) {
    auto entry = day4::parseLine("5-7,7-9");
    ASSERT_TRUE(entry.first.overlapRange(entry.second));
    ASSERT_TRUE(entry.second.overlapRange(entry.first));
}

TEST(Range, overlapRange_onNonOverlappedRange_retrunsFalse) {
    auto entry = day4::parseLine("2-3,4-5");
    ASSERT_FALSE(entry.first.overlapRange(entry.second));
    ASSERT_FALSE(entry.second.overlapRange(entry.first));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}