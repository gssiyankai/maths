#include <gtest/gtest.h>
#include "polynomial.hpp"

using namespace std;

TEST(PolynomialTest, PolynomialToString)
{
    ASSERT_EQ("0", Polynomial(0).str());
    ASSERT_EQ("1", Polynomial(1).str());
    ASSERT_EQ("16", Polynomial(22).str());
}

TEST(PolynomialTest, StringToPolynomial)
{
    ASSERT_EQ(0, Polynomial("").coeffs());
    ASSERT_EQ(0, Polynomial("0").coeffs());
    ASSERT_EQ(13, Polynomial("D").coeffs());
}

TEST(PolynomialTest, Derivative)
{
    ASSERT_EQ(Polynomial("0"), Polynomial("0").derivative());
    ASSERT_EQ(Polynomial("0"), Polynomial("1").derivative());
    ASSERT_EQ(Polynomial("1"), Polynomial("2").derivative());
    ASSERT_EQ(Polynomial("14"), Polynomial("29").derivative());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
