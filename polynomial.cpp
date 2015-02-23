#include "polynomial.hpp"
#include "utils.hpp"
#include <sstream>
#include <algorithm>

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
    while(n > 1)
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
        unsigned int g = gcd(fp, (((unsigned int)1) << pow2(i)) | 2);
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

vector< pair<Polynomial, Polynomial> > Polynomial::pair_factorize(unsigned int d) const
{
    vector< pair<Polynomial, Polynomial> > result;

    const vector<Polynomial>& factors = factorize();
    const vector< pair< vector<Polynomial>, vector<Polynomial> > > pair_factors =  Utils::split(factors);
    for(int i = 0; i < pair_factors.size(); ++i)
    {
        const Polynomial& factor1 = multiply(pair_factors[i].first);
        const Polynomial& factor2 = multiply(pair_factors[i].second);

        if(degree(factor1.coeffs_) <= d && degree(factor2.coeffs_) <= d)
        {
            result.push_back(make_pair(factor1, factor2));
        }
    }

    return result;
}

Polynomial Polynomial::multiply(const vector<Polynomial> &ps)
{
    Polynomial r = ps[0];
    for(int i = 1; i < ps.size(); ++i)
    {
        r = r.multiply(ps[i]);
    }
    return r;
}

vector<Polynomial> Polynomial::factorize_berlekamp() const
{
    vector< vector<int> > q = berlekamp_qmatrix(coeffs_);
    vector< vector<int> > v = berlekamp_qbasis(q);

    for(int i = 0; i < v.size(); ++i)
    {
        while(v[i].back() == 0)
        {
            v[i].pop_back();
        }
        reverse(v[i].begin(), v[i].end());
    }

    vector<Polynomial> factors;
    factors.push_back(Polynomial(coeffs_));

    for(int k = 0; k < v.size(); ++k)
    {
        vector<Polynomial> fs(factors);
        for(auto i = fs.begin(); i != fs.end(); ++i)
        {
            unsigned int f = i->coeffs_;
            int s = 0;

            while(s < 2)
            {
                unsigned int sv = 0;
                for(int j = 0; j < v[k].size(); ++j)
                {

                }
                unsigned int g =
                ++s;
            }
        }
    }

    return factors;
}

vector< vector<int> > Polynomial::berlekamp_qmatrix(unsigned int f)
{
    unsigned int n = degree(f);
    vector<int> q;
    q.push_back(1);
    q.insert(q.end(), n-1, 0);

    vector< vector<int> > qm;
    qm.push_back(q);
    qm.insert(qm.end(), n-1, vector<int>());

    for(int i = 0; i < (n-1)*2; ++i)
    {
        int c = q[q.size()-1];
        vector<int> qq;
        qq.push_back(c * (f & 1));

        for(int j = 1; j < n; ++j)
        {
            qq.push_back(q[j] ^ c * ((f >> j) & 1));
        }

        if(i%2 == 1)
        {
            qm[(i+1)/2] = vector<int>(qq);
        }

        q = qq;
    }

    return qm;
}

vector< vector<int> > Polynomial::berlekamp_qbasis(const vector< vector<int> > &qmatrix)
{
    vector< vector<int> > q(qmatrix);
    unsigned int n = qmatrix.size();

    for(int k = 0; k < n; ++k)
    {
        q[k][k] = q[k][k] ^ 1;
    }

    for(int k = 0; k < n; ++k)
    {
        int i = k;

        for(; i < n; ++i)
        {
            if(q[k][i] == 1)
            {
                break;
            }
        }

        for(int j = 0; j < n; ++j)
        {
            int t = q[j][k];
            q[j][k] = q[j][i];
            q[j][i] = t;
        }

        for(i = 0; i < n; ++i)
        {
            if(i != k)
            {
                int sq = q[k][i];

                for(int j = 0; j < n; ++j)
                {
                    q[j][i] = q[j][i] ^ (q[j][k] * sq);
                }
            }
        }
    }

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(i == j)
            {
                q[i][j] = 1 ^ q[i][j];
            }
        }
    }

    vector< vector<int> > basic;
    for(int i = 0; i < q.size(); ++i)
    {
        for(int j = 0; j < q[i].size(); ++j)
        {
            if(q[i][j]==1)
            {
                basic.push_back(q[i]);
                break;
            }
        }
    }
    return basic;
}
