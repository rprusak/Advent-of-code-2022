#include <gtest/gtest.h>

#include "common.h"
#include "day11.h"

TEST(day11, parseLine) {
    const auto input = common::readInput("../test_input.txt");
    const auto monkeys = day11::parseInput(input);

    ASSERT_EQ(monkeys.size(), 4u);

    ASSERT_EQ(monkeys[0].itemsWorryLevels.size(), 2u);
    ASSERT_EQ(monkeys[0].itemsWorryLevels[0], 79u);
    ASSERT_EQ(monkeys[0].itemsWorryLevels[1], 98u);
    ASSERT_TRUE(monkeys[0].operation == day11::OPERATION::MULTIPLY);
    ASSERT_TRUE(std::holds_alternative<uint64_t>(monkeys[0].operationValue));
    ASSERT_EQ(std::get<uint64_t>(monkeys[0].operationValue), 19u);
    ASSERT_EQ(monkeys[0].testValue, 23u);
    ASSERT_EQ(monkeys[0].trueTarget, 2u);
    ASSERT_EQ(monkeys[0].falseTarget, 3u);

    ASSERT_EQ(monkeys[1].itemsWorryLevels.size(), 4u);
    ASSERT_EQ(monkeys[1].itemsWorryLevels[0], 54u);
    ASSERT_EQ(monkeys[1].itemsWorryLevels[1], 65u);
    ASSERT_EQ(monkeys[1].itemsWorryLevels[2], 75u);
    ASSERT_EQ(monkeys[1].itemsWorryLevels[3], 74u);
    ASSERT_TRUE(monkeys[1].operation == day11::OPERATION::ADD);
    ASSERT_TRUE(std::holds_alternative<uint64_t>(monkeys[1].operationValue));
    ASSERT_EQ(std::get<uint64_t>(monkeys[1].operationValue), 6u);
    ASSERT_EQ(monkeys[1].testValue, 19u);
    ASSERT_EQ(monkeys[1].trueTarget, 2u);
    ASSERT_EQ(monkeys[1].falseTarget, 0u);

    ASSERT_EQ(monkeys[2].itemsWorryLevels.size(), 3u);
    ASSERT_EQ(monkeys[2].itemsWorryLevels[0], 79u);
    ASSERT_EQ(monkeys[2].itemsWorryLevels[1], 60u);
    ASSERT_EQ(monkeys[2].itemsWorryLevels[2], 97u);
    ASSERT_TRUE(monkeys[2].operation == day11::OPERATION::MULTIPLY);
    ASSERT_TRUE(std::holds_alternative<std::string>(monkeys[2].operationValue));
    ASSERT_EQ(std::get<std::string>(monkeys[2].operationValue), "old");
    ASSERT_EQ(monkeys[2].testValue, 13u);
    ASSERT_EQ(monkeys[2].trueTarget, 1u);
    ASSERT_EQ(monkeys[2].falseTarget, 3u);

    ASSERT_EQ(monkeys[3].itemsWorryLevels.size(), 1u);
    ASSERT_EQ(monkeys[3].itemsWorryLevels[0], 74u);
    ASSERT_TRUE(monkeys[3].operation == day11::OPERATION::ADD);
    ASSERT_TRUE(std::holds_alternative<uint64_t>(monkeys[3].operationValue));
    ASSERT_EQ(std::get<uint64_t>(monkeys[3].operationValue), 3u);
    ASSERT_EQ(monkeys[3].testValue, 17u);
    ASSERT_EQ(monkeys[3].trueTarget, 0u);
    ASSERT_EQ(monkeys[3].falseTarget, 1u);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
