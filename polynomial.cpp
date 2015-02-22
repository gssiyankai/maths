#include "polynomial.hpp"
#include "utils.hpp"
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
        unsigned int t = (((unsigned int)1) << (degree(r) - degree(d)));
        q ^= t;
        r ^= multiply(t, d);
    }

    result.push_back(Polynomial(q));
    result.push_back(Polynomial(r));
    return result;
}

unsigned int Polynomial::degree(unsigned int n)
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
        unsigned int t = (((unsigned int)1) << (degree(r) - degree(d)));
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
        unsigned int t = (((unsigned int)1) << (degree(r) - degree(d)));
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
    vector<Polynomial> fs;
    unsigned int i = 1;
    unsigned  int f = coeffs_;
    unsigned int fp = f;
    while(degree(fp) > 2*i)
    {
        unsigned int g = gcd(fp, (1 << pow2(i)) | 2);
        if(g != 1)
        {
            fs.push_back(Polynomial(g));
            fp = quotient(fp, g);
        }
        ++i;
    }
    if(fp != 1)
    {
        fs.push_back(fp);
    }
    if(fs.empty())
    {
        fs.push_back(f);
    }
    return fs;
}

unsigned int Polynomial::pow2(unsigned int n)
{
    unsigned int p = 2;
    while(--n > 0)
    {
        p = p << 1;
    }
    return p;
}

vector< pair<Polynomial, Polynomial> > Polynomial::pair_factorize() const
{
    vector< pair<Polynomial, Polynomial> > result;

    const vector<Polynomial>& factors = factorize();
    const vector< pair< vector<Polynomial>, vector<Polynomial> > > pair_factors =  Utils::split(factors);
    for(int i = 0; i < pair_factors.size(); ++i)
    {
        result.push_back(
                make_pair(
                        multiply(pair_factors[i].first),
                        multiply(pair_factors[i].second)));
    }

    return result;
}

Polynomial Polynomial::multiply(const std::vector<Polynomial> &ps)
{
    Polynomial r = ps[0];
    for(int i = 1; i < ps.size(); ++i)
    {
        r = r.multiply(ps[i]);
    }
    return r;
}
