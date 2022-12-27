#include <gtest/gtest.h>

#include "day25.h"

TEST(day25, convertToDecimal) {
    ASSERT_EQ(day25::convertToDecimal("1=-0-2"), 1747);
    ASSERT_EQ(day25::convertToDecimal("12111"), 906);
    ASSERT_EQ(day25::convertToDecimal("2=0="), 198);
    ASSERT_EQ(day25::convertToDecimal("21"), 11);
    ASSERT_EQ(day25::convertToDecimal("2=01"), 201);
    ASSERT_EQ(day25::convertToDecimal("111"), 31);
    ASSERT_EQ(day25::convertToDecimal("20012"), 1257);
    ASSERT_EQ(day25::convertToDecimal("112"), 32);
    ASSERT_EQ(day25::convertToDecimal("1=-1="), 353);
    ASSERT_EQ(day25::convertToDecimal("1-12"), 107);
    ASSERT_EQ(day25::convertToDecimal("12"), 7);
    ASSERT_EQ(day25::convertToDecimal("1="), 3);
    ASSERT_EQ(day25::convertToDecimal("122"), 37);
}

TEST(day25, convertToSNAFU) {
    ASSERT_EQ(day25::convertToSNAFU(1747), "1=-0-2");
    ASSERT_EQ(day25::convertToSNAFU(7), "12");
    ASSERT_EQ(day25::convertToSNAFU(11), "21");
    ASSERT_EQ(day25::convertToSNAFU(31), "111");
    ASSERT_EQ(day25::convertToSNAFU(37), "122");
    ASSERT_EQ(day25::convertToSNAFU(906), "12111");
    ASSERT_EQ(day25::convertToSNAFU(1257), "20012");
    ASSERT_EQ(day25::convertToSNAFU(3), "1=");
    ASSERT_EQ(day25::convertToSNAFU(198), "2=0=");
    ASSERT_EQ(day25::convertToSNAFU(201), "2=01");
    ASSERT_EQ(day25::convertToSNAFU(353), "1=-1=");
    ASSERT_EQ(day25::convertToSNAFU(107), "1-12");
    ASSERT_EQ(day25::convertToSNAFU(4890), "2=-1=0");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}