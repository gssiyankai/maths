#include "polynomial.hpp"
#include <iomanip>
#include <sstream>

using namespace std;

Polynomial::Polynomial(const std::string& value)
{
    stringstream stream;
    stream << hex << value;
    stream >> coeffs_;
}

Polynomial::Polynomial(unsigned int coeffs) : coeffs_(coeffs)
{
}

bool Polynomial::operator==(const Polynomial &o) const
{
    return coeffs_ == o.coeffs_;
}

unsigned int Polynomial::coeffs() const
{
    return coeffs_;
}

string Polynomial::str() const
{
    stringstream stream;
    stream << hex << coeffs_;
    return stream.str();
}

Polynomial Polynomial::derivative() const
{
    return Polynomial(coeffs_ >> 1);
}

Polynomial Polynomial::multiply(const Polynomial& m) const
{
    return Polynomial(multiply(coeffs_, m.coeffs_));
}

unsigned int Polynomial::multiply(unsigned int n, unsigned int m) const
{
    unsigned int r = 0;
    unsigned int i = 0;
    while(m > 0)
    {
        if((m & 1) == 1)
        {
            r ^= (n << i);
        }
        m = m >> 1;
        ++i;
    }
    return r;
}

vector<Polynomial> Polynomial::divide(const Polynomial &divisor) const
{
    vector<Polynomial> result;

    unsigned int d = divisor.coeffs_;
    unsigned int q = 0;
    unsigned int r = coeffs_;

    while(r != 0 && r >= d)
    {
        unsigned int t = (((unsigned int)1) << (lead(r) - lead(d)));
        q ^= t;
        r ^= multiply(t, d);
    }

    result.push_back(Polynomial(q));
    result.push_back(Polynomial(r));
    return result;
}

unsigned int Polynomial::lead(unsigned int n) const
{
    unsigned int i = 0;
    while(n > 0)
    {
        n = n >> 1;
        ++i;
    }
    return i;
}

unsigned int Polynomial::remainder(unsigned int dividend, unsigned int divisor) const
{
    unsigned int d = divisor;
    unsigned int r = dividend;

    while(r != 0 && r >= d)
    {
        unsigned int t = (((unsigned int)1) << (lead(r) - lead(d)));
        r ^= multiply(t, d);
    }

    return r;
}

Polynomial Polynomial::gcd(const Polynomial &p) const
{
    unsigned int a = coeffs_;
    unsigned int b = p.coeffs_;

    unsigned int r = 0;

    do
    {
        r = remainder(a, b);
        a = b;
        b = r;
    } while(b != 0);

    return Polynomial(a);
}

vector<Polynomial> Polynomial::factorize() const
{
    vector<Polynomial> result;
    result.push_back(*this);
    return result;
}
