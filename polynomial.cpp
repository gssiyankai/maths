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
    return Polynomial(derivative(coeffs_));
}

unsigned int Polynomial::derivative(unsigned int n)
{
    return (n >> 1) & 0x55555555;
}

Polynomial Polynomial::multiply(const Polynomial& m) const
{
    return Polynomial(multiply(coeffs_, m.coeffs_));
}

unsigned int Polynomial::multiply(unsigned int n, unsigned int m)
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

unsigned int Polynomial::lead(unsigned int n)
{
    unsigned int i = 0;
    while(n > 0)
    {
        n = n >> 1;
        ++i;
    }
    return i;
}

unsigned int Polynomial::quotient(unsigned int dividend, unsigned int divisor)
{
    unsigned int d = divisor;
    unsigned int q = 0;
    unsigned int r = dividend;

    while(r != 0 && r >= d)
    {
        unsigned int t = (((unsigned int)1) << (lead(r) - lead(d)));
        q ^= t;
        r ^= multiply(t, d);
    }

    return q;
}

unsigned int Polynomial::remainder(unsigned int dividend, unsigned int divisor)
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
    return Polynomial(gcd(coeffs_, p.coeffs_));
}

unsigned int Polynomial::gcd(unsigned int a, unsigned int b)
{
    unsigned int r = 0;

    do
    {
        r = remainder(a, b);
        a = b;
        b = r;
    } while(b != 0);

    return a;
}

vector<Polynomial> Polynomial::factorize() const
{
    if(coeffs_==1)
    {
        vector<Polynomial> result;
        result.push_back(Polynomial(1));
        return result;
    }

    unsigned int i = 1;
    unsigned int r = 1;
    unsigned int f = coeffs_;
    unsigned int g = derivative(f);

    if(g != 0)
    {
        unsigned int c = gcd(f, g);
        unsigned int w = quotient(f, c);
        while(w != 1)
        {
            unsigned int y = gcd(w, c);
                unsigned int z = quotient(w, y);
            unsigned int zi = 1;
            for(int j = 0; j < i; ++j)
            {
                zi = multiply(zi, z);
            }
            r = multiply(r, zi);
            ++i;
            w = y;
            c = quotient(c, y);
        }
        if(c != 1)
        {
            if((c & 1) == 1)
            {
                c = c >> 2;
                c |= 1;
            }
            else
            {
                c = c >> 2;
            }

            vector<Polynomial> result;
            result.push_back(Polynomial(r));
            const vector<Polynomial>& sub_result = Polynomial(c).factorize(); //TODO
            result.insert(result.end(), sub_result.begin(), sub_result.end());
            return result;
        }
        else
        {
            vector<Polynomial> result;
            result.push_back(Polynomial(multiply(r, r)));
            return result;
        }
    }
    else
    {
        if((f & 1) == 1)
        {
            f = f >> 2;
            f |= 1;
        }
        else
        {
            f = f >> 2;
        }
        return Polynomial(f).factorize(); //TODO
    }
}
