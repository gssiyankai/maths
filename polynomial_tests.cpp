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
    ASSERT_EQ(Polynomial("0"), Polynomial("14").derivative());
}

TEST(PolynomialTest, Multiply)
{
    ASSERT_EQ(Polynomial("0"), Polynomial("1").multiply(Polynomial("0")));
    ASSERT_EQ(Polynomial("1"), Polynomial("1").multiply(Polynomial("1")));
    ASSERT_EQ(Polynomial("9"), Polynomial("3").multiply(Polynomial("7")));
    ASSERT_EQ(Polynomial("53"), Polynomial("B").multiply(Polynomial("9")));
    ASSERT_EQ(Polynomial("16"), Polynomial("B").multiply(Polynomial("2")));
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
    {
        const vector<Polynomial>& result = Polynomial("53").divide(Polynomial("B"));
        ASSERT_EQ(Polynomial("9"), result[0]);
        ASSERT_EQ(Polynomial("0"), result[1]);
    }
    {
        const vector<Polynomial>& result = Polynomial("16").divide(Polynomial("B"));
        ASSERT_EQ(Polynomial("2"), result[0]);
        ASSERT_EQ(Polynomial("0"), result[1]);
    }
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
        const vector<Polynomial>& result = Polynomial("1").factorize();
        ASSERT_EQ(1, result.size());
        ASSERT_EQ(Polynomial("1"), result[0]);
    }
    {
        const vector<Polynomial>& result = Polynomial("16").factorize();
        ASSERT_EQ(2, result.size());
        ASSERT_EQ(Polynomial("2"), result[0]);
        ASSERT_EQ(Polynomial("B"), result[1]);
    }
    {
        const vector<Polynomial>& result = Polynomial("53").factorize();
        ASSERT_EQ(3, result.size());
        ASSERT_EQ(Polynomial("3"), result[0]);
        ASSERT_EQ(Polynomial("7"), result[1]);
        ASSERT_EQ(Polynomial("B"), result[2]);
    }
}

TEST(PolynomialTest, PairFactorize)
{
    const vector< pair<Polynomial, Polynomial> >& pair_factors = Polynomial("53").pair_factorize();
    ASSERT_EQ(3, pair_factors.size());
    ASSERT_EQ(make_pair(Polynomial("3"), Polynomial("31")), pair_factors[0]);
    ASSERT_EQ(make_pair(Polynomial("7"), Polynomial("1D")), pair_factors[1]);
    ASSERT_EQ(make_pair(Polynomial("B"), Polynomial("9")), pair_factors[2]);
}

TEST(PolynomialTest, PairFactorizeWithMaxDegree)
{
    const vector< pair<Polynomial, Polynomial> >& pair_factors = Polynomial("53").pair_factorize(3);
    ASSERT_EQ(1, pair_factors.size());
    ASSERT_EQ(make_pair(Polynomial("B"), Polynomial("9")), pair_factors[0]);
}

TEST(PolynomialTest, BerlekampQMatrix)
{
    {
        const vector< vector<int> >& result = Polynomial::berlekamp_qmatrix(Polynomial("73AF").coeffs());
        const vector< vector<int> > expected = { { 1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
                                                 { 0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
                                                 { 0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
                                                 { 0,0,0,0,0,0,1,0,0,0,0,0,0,0 },
                                                 { 0,0,0,0,0,0,0,0,1,0,0,0,0,0 },
                                                 { 0,0,0,0,0,0,0,0,0,0,1,0,0,0 },
                                                 { 0,0,0,0,0,0,0,0,0,0,0,0,1,0 },
                                                 { 1,1,1,1,0,1,0,1,1,1,0,0,1,1 },
                                                 { 0,1,0,0,0,1,1,1,1,0,0,1,0,1 },
                                                 { 1,0,0,1,1,1,1,0,1,1,0,0,1,1 },
                                                 { 0,1,0,1,1,1,0,1,0,1,0,1,0,1 },
                                                 { 1,0,0,1,1,0,0,0,0,1,1,1,1,1 },
                                                 { 0,1,0,1,1,1,0,0,1,1,1,1,1,0 },
                                                 { 1,1,1,0,0,0,1,0,1,1,1,1,0,0 } };
        ASSERT_EQ(expected, result);
    }
}

TEST(PolynomialTest, BerlekampQBasis)
{
    const vector< vector<int> >& result = Polynomial::berlekamp_qbasis(
                                                Polynomial::berlekamp_qmatrix(Polynomial("73AF").coeffs()));
    const vector< vector<int> > expected = { { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                             { 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0 },
                                             { 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0 },
                                             { 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1 } };
    ASSERT_EQ(expected, result);
}

TEST(PolynomialTest, FactorizeBerlekamp)
{
    {
        const vector<Polynomial>& result = Polynomial("73AF").factorize_berlekamp();
        ASSERT_EQ(2, result.size());
        ASSERT_EQ(Polynomial("83"), result[0]);
        ASSERT_EQ(Polynomial("e5"), result[1]);
    }
    {
        const vector<Polynomial>& result = Polynomial("738377c1").factorize_berlekamp();
        ASSERT_EQ(2, result.size());
        ASSERT_EQ(Polynomial("b0c5"), result[0]);
        ASSERT_EQ(Polynomial("cd55"), result[1]);
    }
}
