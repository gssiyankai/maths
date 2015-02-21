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

TEST(PolynomialTest, Multiply)
{
    ASSERT_EQ(Polynomial("0"), Polynomial("1").multiply(Polynomial("0")));
    ASSERT_EQ(Polynomial("1"), Polynomial("1").multiply(Polynomial("1")));
    ASSERT_EQ(Polynomial("9"), Polynomial("3").multiply(Polynomial("7")));
}

TEST(PolynomialTest, Divide)
{
    {
        const vector<Polynomial>& result = Polynomial("1").divide(Polynomial("1"));
        ASSERT_EQ(Polynomial("1"), result[0]);
        ASSERT_EQ(Polynomial("0"), result[1]);
    }
    {
        const vector<Polynomial>& result = Polynomial("95").divide(Polynomial("3"));
        ASSERT_EQ(Polynomial("73"), result[0]);
        ASSERT_EQ(Polynomial("0"), result[1]);
    }
    {
        const vector<Polynomial>& result = Polynomial("D").divide(Polynomial("3"));
        ASSERT_EQ(Polynomial("4"), result[0]);
        ASSERT_EQ(Polynomial("1"), result[1]);
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
