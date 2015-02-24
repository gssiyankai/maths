#include "polynomial.hpp"
#include "utils.hpp"
#include <sstream>
#include <algorithm>
#include <stack>

using namespace std;

Polynomial::Polynomial(const std::string& value)
{
    for(int i = 0; i < value.size(); ++i)
    {
        char c = value[i];
        if(c == ' ')
        {
            continue;
        }
        stringstream s;
        s << hex << c;

        unsigned int x;
        s >> x;
        for(int j = 0; j < 4; ++j)
        {
            int bit = ( (x >> (3 - j)) & 1);
            coeffs_.push_back(bit);
        }
    }
}

Polynomial::Polynomial(vector<int> coeffs) : coeffs_(coeffs)
{
}

bool Polynomial::operator==(const Polynomial &o) const
{
    return coeffs_ == o.coeffs_;
}

vector<int> Polynomial::coeffs() const
{
    return coeffs_;
}

string Polynomial::str() const
{
    stack<string> cs;

    unsigned int x = 0;
    for(int i = 0; i < coeffs_.size(); ++i)
    {
        x |= coeffs_ [coeffs_.size()-1-i] << (i % 32);
        if(((i+1) % 32) == 0 || i == coeffs_.size()-1)
        {
            stringstream s;
            s << hex << x;
            cs.push(s.str());
            x = 0;
        }
    }

    string str;
    while(!cs.empty())
    {
        str += cs.top();
        cs.pop();
        if(!cs.empty())
        {
            str += " ";
        }
    }

    return str;
}

//Polynomial Polynomial::multiply(const Polynomial& m) const
//{
//    return Polynomial(multiply(coeffs_, m.coeffs_));
//}
//
//unsigned int Polynomial::multiply(unsigned int n, unsigned int m)
//{
//    unsigned int r = 0;
//    unsigned int i = 0;
//    while(m > 0)
//    {
//        if((m & 1) == 1)
//        {
//            r ^= (n << i);
//        }
//        m = m >> 1;
//        ++i;
//    }
//    return r;
//}
//
//unsigned int Polynomial::degree(unsigned int n)
//{
//    unsigned int i = 0;
//    while(n > 1)
//    {
//        n = n >> 1;
//        ++i;
//    }
//    return i;
//}
//
//unsigned int Polynomial::quotient(unsigned int dividend, unsigned int divisor)
//{
//    unsigned int d = divisor;
//    unsigned int q = 0;
//    unsigned int r = dividend;
//
//    while(r != 0 && r >= d)
//    {
//        unsigned int t = (((unsigned int)1) << (degree(r) - degree(d)));
//        q ^= t;
//        r ^= multiply(t, d);
//    }
//
//    return q;
//}
//
//unsigned int Polynomial::remainder(unsigned int dividend, unsigned int divisor)
//{
//    unsigned int d = divisor;
//    unsigned int r = dividend;
//
//    while(r != 0 && r >= d)
//    {
//        unsigned int t = (((unsigned int)1) << (degree(r) - degree(d)));
//        r ^= multiply(t, d);
//    }
//
//    return r;
//}
//
//Polynomial Polynomial::gcd(const Polynomial &p) const
//{
//    return Polynomial(gcd(coeffs_, p.coeffs_));
//}
//
//unsigned int Polynomial::gcd(unsigned int a, unsigned int b)
//{
//    unsigned int r = 0;
//
//    do
//    {
//        r = remainder(a, b);
//        a = b;
//        b = r;
//    } while(b != 0);
//
//    return a;
//}
//
//vector<Polynomial> Polynomial::factorize_berlekamp() const
//{
//    vector< vector<int> > q = berlekamp_qmatrix(coeffs_);
//    vector< vector<int> > v = berlekamp_qbasis(q);
//
//    for(int i = 0; i < v.size(); ++i)
//    {
//        while(v[i].back() == 0)
//        {
//            v[i].pop_back();
//        }
//    }
//
//    vector<unsigned int> factors;
//    factors.push_back(coeffs_);
//
//    for(int k = 1; k < v.size(); ++k)
//    {
//        vector<unsigned int> fs(factors);
//        for(auto i = fs.begin(); i != fs.end(); ++i)
//        {
//            unsigned int f = *i;
//            int s = 0;
//
//            while(s < 2)
//            {
//                unsigned int sv = 0;
//                for(int j = 0; j < v[k].size(); ++j)
//                {
//                    sv |= (v[k][j] << j);
//                }
//                unsigned int g = sub_ground(sv, s);
//                unsigned int h = gcd(f, g);
//
//                if(h != 1 && h != f)
//                {
//                    for(auto j = factors.begin(); j != factors.end(); ++j)
//                    {
//                        if(*j ==f)
//                        {
//                            factors.erase(j);
//                            break;
//                        }
//                    }
//
//                    f = quotient(f, h);
//                    factors.push_back(f);
//                    factors.push_back(h);
//                }
//
//                if(factors.size() == v.size())
//                {
//                    vector<Polynomial> result;
//                    for(int i = 0; i < factors.size(); ++i)
//                    {
//                        result.push_back(Polynomial(factors[i]));
//                    }
//                    return result;
//                }
//                ++s;
//            }
//        }
//    }
//
//    vector<Polynomial> result;
//    for(int i = 0; i < factors.size(); ++i)
//    {
//        result.push_back(Polynomial(factors[i]));
//    }
//    return result;
//}
//
//unsigned int Polynomial::sub_ground(unsigned int f, unsigned int a)
//{
//    if(f != 0)
//    {
//        a = (f & 1) ^ a;
//        if((f & ~1) != 0)
//        {
//            return (f & ~1) + a;
//        }
//    }
//
//    if(a==0)
//    {
//        return 0;
//    }
//    else
//    {
//        return a;
//    }
//}
//
//vector< vector<int> > Polynomial::berlekamp_qmatrix(unsigned int f)
//{
//    unsigned int n = degree(f);
//    vector<int> q;
//    q.push_back(1);
//    q.insert(q.end(), n-1, 0);
//
//    vector< vector<int> > qm;
//    qm.push_back(q);
//    qm.insert(qm.end(), n-1, vector<int>());
//
//    for(int i = 0; i < (n-1)*2; ++i)
//    {
//        int c = q[q.size()-1];
//        vector<int> qq;
//        qq.push_back(c * (f & 1));
//
//        for(int j = 1; j < n; ++j)
//        {
//            qq.push_back(q[j-1] ^ c * ((f >> j) & 1));
//        }
//
//        if(i%2 == 1)
//        {
//            qm[(i+1)/2] = vector<int>(qq);
//        }
//
//        q = qq;
//    }
//
//    return qm;
//}
//
//vector< vector<int> > Polynomial::berlekamp_qbasis(const vector< vector<int> > &qmatrix)
//{
//    vector< vector<int> > q(qmatrix);
//    unsigned int n = qmatrix.size();
//
//    for(int k = 0; k < n; ++k)
//    {
//        q[k][k] = q[k][k] ^ 1;
//    }
//
//    for(int k = 0; k < n; ++k)
//    {
//        int i = k;
//
//        for(; i < n; ++i)
//        {
//            if(q[k][i] == 1)
//            {
//                break;
//            }
//        }
//
//        if(i == n)
//        {
//            continue;
//        }
//
//        for(int j = 0; j < n; ++j)
//        {
//            int t = q[j][k];
//            q[j][k] = q[j][i];
//            q[j][i] = t;
//        }
//
//        for(i = 0; i < n; ++i)
//        {
//            if(i != k)
//            {
//                int sq = q[k][i];
//
//                for(int j = 0; j < n; ++j)
//                {
//                    q[j][i] = q[j][i] ^ (q[j][k] * sq);
//                }
//            }
//        }
//    }
//
//    for(int i = 0; i < n; ++i)
//    {
//        for(int j = 0; j < n; ++j)
//        {
//            if(i == j)
//            {
//                q[i][j] = 1 ^ q[i][j];
//            }
//        }
//    }
//
//    vector< vector<int> > basic;
//    for(int i = 0; i < q.size(); ++i)
//    {
//        for(int j = 0; j < q[i].size(); ++j)
//        {
//            if(q[i][j]==1)
//            {
//                basic.push_back(q[i]);
//                break;
//            }
//        }
//    }
//    return basic;
//}
