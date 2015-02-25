#include <gtest/gtest.h>
#include "polynomial.hpp"

using namespace std;

TEST(PolynomialTest, PolynomialToString)
{
    ASSERT_EQ("0", Polynomial(vector<int>({0})).str());
    ASSERT_EQ("1", Polynomial(vector<int>({1})).str());
    ASSERT_EQ("16", Polynomial(vector<int>({1,0,1,1,0})).str());
    ASSERT_EQ("6677e201 46508fb7", Polynomial(vector<int>({  1,1,0,0,1,1,0,0,1,1,1,0,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,
                                                           0,1,0,0,0,1,1,0,0,1,0,1,0,0,0,0,1,0,0,0,1,1,1,1,1,0,1,1,0,1,1,1})).str());
}

TEST(PolynomialTest, StringToPolynomial)
{
    ASSERT_EQ(vector<int>({0}), Polynomial("0").coeffs());
    ASSERT_EQ(vector<int>({1}), Polynomial("1").coeffs());
    ASSERT_EQ(vector<int>({1,1,0,1}), Polynomial("D").coeffs());
    ASSERT_EQ(vector<int>({  1,1,0,0,1,1,0,0,1,1,1,0,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,
                           0,1,0,0,0,1,1,0,0,1,0,1,0,0,0,0,1,0,0,0,1,1,1,1,1,0,1,1,0,1,1,1}),
              Polynomial("6677e201 46508fb7").coeffs());
}

TEST(PolynomialTest, Degree)
{
    ASSERT_EQ(0, Polynomial("0").degree());
    ASSERT_EQ(0, Polynomial("1").degree());
    ASSERT_EQ(2, Polynomial("7").degree());
    ASSERT_EQ(62, Polynomial("6677e201 46508fb7").degree());
}

TEST(PolynomialTest, Multiply)
{
    ASSERT_EQ(Polynomial("0"), Polynomial("1").multiply(Polynomial("0")));
    ASSERT_EQ(Polynomial("1"), Polynomial("1").multiply(Polynomial("1")));
    ASSERT_EQ(Polynomial("9"), Polynomial("3").multiply(Polynomial("7")));
    ASSERT_EQ(Polynomial("53"), Polynomial("B").multiply(Polynomial("9")));
    ASSERT_EQ(Polynomial("16"), Polynomial("B").multiply(Polynomial("2")));
}

TEST(PolynomialTest, Gcd)
{
    ASSERT_EQ(Polynomial("1"), Polynomial("1").gcd(Polynomial("1")));
    ASSERT_EQ(Polynomial("73"), Polynomial("95").gcd(Polynomial("73")));
    ASSERT_EQ(Polynomial("B"), Polynomial("53").gcd(Polynomial("16")));
}

TEST(PolynomialTest, Factorize)
{
    {
        const vector<Polynomial>& result = Polynomial("73AF").factorize();
        ASSERT_EQ(2, result.size());
        ASSERT_EQ(Polynomial("83"), result[0]);
        ASSERT_EQ(Polynomial("e5"), result[1]);
    }
    {
        const vector<Polynomial>& result = Polynomial("738377c1").factorize();
        ASSERT_EQ(2, result.size());
        ASSERT_EQ(Polynomial("b0c5"), result[0]);
        ASSERT_EQ(Polynomial("cd55"), result[1]);
    }
    {
        const vector<Polynomial>& result = Polynomial("53").factorize();
        ASSERT_EQ(3, result.size());
        ASSERT_EQ(Polynomial("7"), result[0]);
        ASSERT_EQ(Polynomial("3"), result[1]);
        ASSERT_EQ(Polynomial("B"), result[2]);
    }
    {
        const vector<Polynomial>& result = Polynomial("16").factorize();
        ASSERT_EQ(2, result.size());
        ASSERT_EQ(Polynomial("B"), result[0]);
        ASSERT_EQ(Polynomial("2"), result[1]);
    }
    {
        const vector<Polynomial>& result = Polynomial("6677e2014 6508fb7").factorize();
        ASSERT_EQ(2, result.size());
        ASSERT_EQ(Polynomial("b0c152f9"), result[0]);
        ASSERT_EQ(Polynomial("ebf2831f"), result[1]);
    }
}
