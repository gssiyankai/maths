#include <gtest/gtest.h>
#include "polynomial.hpp"

using namespace std;

TEST(PolynomialTest, PolynomialToString)
{
    ASSERT_EQ("0", Polynomial(vector<int>()).str());
    ASSERT_EQ("1", Polynomial(vector<int>({ 1 })).str());
    ASSERT_EQ("0", Polynomial(vector<int>({ 0 })).str());
    ASSERT_EQ("16", Polynomial(vector<int>({0, 1, 1, 0, 1})).str());
}

TEST(PolynomialTest, StringToPolynomial)
{
    ASSERT_EQ(vector<int>({0}), Polynomial("").coeffs());
    ASSERT_EQ(vector<int>({0}), Polynomial("0").coeffs());
    ASSERT_EQ(vector<int>({1, 0, 1, 1}), Polynomial("D").coeffs());
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
