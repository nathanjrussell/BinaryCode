#include <gtest/gtest.h>
#include "BinaryCodeWord.hpp"
#include "BinaryCodeGenMat.hpp"
#include "BinaryCode.hpp"

TEST(BinaryCode, RankAndForms) {
    BinaryCodeWord r0(5), r1(5), r2(5);
    r0.setBit(2,1); r0.setBit(0,1);
    r1.setBit(2,1); r1.setBit(1,1);
    r2 = r0 + r1;
    BinaryCodeGenMat G({r0, r1, r2});
    BinaryCode C(G);
    EXPECT_EQ(C.length(), 5);
    EXPECT_EQ(C.dimension(), 2);
    EXPECT_EQ(C.rref().numRows(), 2);
    const auto& S = C.systematic();
    ASSERT_EQ(S.numRows(), 2);
    EXPECT_EQ(S[0].getBit(0), 1);
    EXPECT_EQ(S[1].getBit(0), 0);
    EXPECT_EQ(S[0].getBit(1), 0);
    EXPECT_EQ(S[1].getBit(1), 1);
}
