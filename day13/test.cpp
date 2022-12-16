#include <gtest/gtest.h>

#include "day13.h"

TEST(day13, areInValidOrder) {
    ASSERT_TRUE(day13::areInValidOrder("[1,1,3,1,1]", "[1,1,5,1,1]"));
    ASSERT_TRUE(day13::areInValidOrder("[[1],[2,3,4]]", "[[1],4]"));
    ASSERT_FALSE(day13::areInValidOrder("[9]", "[[8,7,6]]"));
    ASSERT_TRUE(day13::areInValidOrder("[[4,4],4,4]", "[[4,4],4,4,4]"));
    ASSERT_FALSE(day13::areInValidOrder("[7,7,7,7]", "[7,7,7]"));
    ASSERT_TRUE(day13::areInValidOrder("[]", "[3]"));
    ASSERT_FALSE(day13::areInValidOrder("[[[]]]", "[[]]"));
    ASSERT_FALSE(
        day13::areInValidOrder("[1,[2,[3,[4,[5,6,7]]]],8,9]", "[1,[2,[3,[4,[5,6,0]]]],8,9]"));

    ASSERT_TRUE(day13::areInValidOrder("[[[],[],[],4,[[10,9,7],[10,1],[4,8,4,0,7],7]],[]]",
                                       "[[6,0,[],3]]"));
}

TEST(day13, parseSimplePacket) {
    auto packet = day13::parsePacket("[1,1,5,1,1]");
    ASSERT_EQ(packet.size(), 5u);

    for (unsigned i = 0; i < 5; i++) ASSERT_TRUE(day13::isNumber(packet[i]));

    ASSERT_EQ(day13::getNumber(packet[0]), 1u);
    ASSERT_EQ(day13::getNumber(packet[1]), 1u);
    ASSERT_EQ(day13::getNumber(packet[2]), 5u);
    ASSERT_EQ(day13::getNumber(packet[3]), 1u);
    ASSERT_EQ(day13::getNumber(packet[4]), 1u);
}

TEST(day13, parseComplexPacket) {
    auto packet = day13::parsePacket("[1,[2,[3,[4,[5,6,7]]]],8,9]");
    ASSERT_EQ(packet.size(), 4u);

    ASSERT_TRUE(day13::isNumber(packet[0]));
    ASSERT_TRUE(day13::isList(packet[1]));
    ASSERT_TRUE(day13::isNumber(packet[2]));
    ASSERT_TRUE(day13::isNumber(packet[3]));

    auto v = day13::getList(packet[1]);
    ASSERT_EQ(v.size(), 2u);

    ASSERT_TRUE(day13::isNumber(v[0]));
    ASSERT_TRUE(day13::getNumber(v[0]) == 2u);
    ASSERT_TRUE(day13::isList(v[1]));
}

TEST(day13, parseComplexPacket2) {
    auto packet = day13::parsePacket("[[[[3,5,5,0],3,8,9]]]");
    ASSERT_EQ(packet.size(), 1u);
    ASSERT_TRUE(day13::isList(packet[0]));

    auto v = day13::getList(packet[0]);
    ASSERT_TRUE(v.size() == 1u);

    ASSERT_TRUE(day13::isList(v[0]));
    v = day13::getList(v[0]);
    ASSERT_TRUE(v.size() == 4u);

    ASSERT_TRUE(day13::isList(v[0]));
    ASSERT_TRUE(day13::isNumber(v[1]));
    ASSERT_TRUE(day13::isNumber(v[2]));
    ASSERT_TRUE(day13::isNumber(v[3]));

    v = day13::getList(v[0]);
    ASSERT_TRUE(v.size() == 4u);
    ASSERT_TRUE(day13::isNumber(v[0]));
    ASSERT_TRUE(day13::getNumber(v[0]) == 3u);
    ASSERT_TRUE(day13::isNumber(v[1]));
    ASSERT_TRUE(day13::getNumber(v[1]) == 5u);
    ASSERT_TRUE(day13::isNumber(v[2]));
    ASSERT_TRUE(day13::getNumber(v[2]) == 5u);
    ASSERT_TRUE(day13::isNumber(v[3]));
    ASSERT_TRUE(day13::getNumber(v[3]) == 0u);
}

TEST(day13, parseComplexPacket3) {
    auto packet = day13::parsePacket("[[[9,[10,4,9]]]]");
    ASSERT_EQ(packet.size(), 1u);
    ASSERT_TRUE(day13::isList(packet[0]));

    auto v = day13::getList(packet[0]);
    ASSERT_TRUE(v.size() == 1u);

    ASSERT_TRUE(day13::isList(v[0]));
    v = day13::getList(v[0]);
    ASSERT_TRUE(v.size() == 2u);

    ASSERT_TRUE(day13::isNumber(v[0]));
    ASSERT_EQ(day13::getNumber(v[0]), 9u);
    ASSERT_TRUE(day13::isList(v[1]));
    v = day13::getList(v[1]);
    ASSERT_EQ(v.size(), 3u);
    ASSERT_TRUE(day13::isNumber(v[0]));
    ASSERT_EQ(day13::getNumber(v[0]), 10u);
    ASSERT_TRUE(day13::isNumber(v[1]));
    ASSERT_EQ(day13::getNumber(v[1]), 4u);
    ASSERT_TRUE(day13::isNumber(v[2]));
    ASSERT_EQ(day13::getNumber(v[2]), 9u);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}