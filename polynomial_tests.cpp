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
    ASSERT_EQ(vector<int>({1, 0, 1, 1}), Polynomial("D").coeffs());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
