#include "polynomial.hpp"
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
    coeffs_ = strip(coeffs_);
}

Polynomial::Polynomial(vector<int> coeffs) : coeffs_(strip(coeffs))
{
}

vector<int> Polynomial::strip(const vector<int>& n)
{
    for(auto i = n.begin(); i != n.end(); ++i)
    {
        if(*i!=0)
        {
            return vector<int>(i, n.end());
        }
    }
    return vector<int>(1,0);
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

unsigned int Polynomial::degree() const
{
    return degree(coeffs_);
}

unsigned int Polynomial::degree(const vector<int>& n)
{
    return n.size() - 1;
}

Polynomial Polynomial::multiply(const Polynomial& m) const
{
    return Polynomial(multiply(coeffs_, m.coeffs_));
}

vector<int> Polynomial::multiply(const vector<int>& n, const vector<int>& m)
{
    int dn = degree(n);
    int dm = degree(m);
    int dp = dn + dm + 1;
    vector<int> p(dp, 0);
    for(int i = 0; i < dp; ++i)
    {
        for(int j = max(0, i - dm); j < min(i, dn) + 1; ++j)
        {
            p[i] ^= n[j] * m[i - j];
        }
    }
    return strip(p);
}

Polynomial Polynomial::gcd(const Polynomial &p) const
{
    return Polynomial(gcd(coeffs_, p.coeffs_));
}

vector<int> Polynomial::gcd(vector<int> f, vector<int> g)
{
    while(g != vector<int>({ 0 }))
    {
        vector<int> r = remainder(f, g);
        f = g;
        g = r;
    }

    return f;
}

vector<int> Polynomial::quotient(const vector<int>& f, const vector<int>& g)
{
    int df = degree(f);
    int dg = degree(g);

    if(df < dg)
    {
        return {};
    }

    vector<int> h(f);
    int dq = df - dg;
    int dr = dg - 1;

    for(int i = 0; i < dq + 1; ++i)
    {
        for(int j = max(0, dg - i); j < min(df - i, dr) + 1; ++j)
        {
            h[i] ^= h[i + j - dg] * g[dg - j];
        }
    }

    return vector<int>(h.begin(), h.begin()+dq+1);
}

vector<int> Polynomial::remainder(const vector<int>& f, const vector<int>& g)
{
    int df = degree(f);
    int dg = degree(g);

    if(df < dg)
    {
        return f;
    }

    vector<int> h(f);
    int dq = df - dg;
    int dr = dg - 1;

    for(int i = 0; i < df + 1; ++i)
    {
        for(int j = max(0, dg - i); j < min(df - i, dr) + 1; ++j)
        {
            h[i] ^= h[i + j - dg] * g[dg - j];
        }
    }

    return strip(vector<int>(h.begin()+dq+1, h.end()));
}

vector<Polynomial> Polynomial::factorize() const
{
    vector< vector<int> > q = berlekamp_qmatrix(coeffs_);
    vector< vector<int> > v = berlekamp_qbasis(q);

    for(int i = 0; i < v.size(); ++i)
    {
        reverse(v[i].begin(), v[i].end());
        v[i] = strip(v[i]);
    }

    vector< vector<int> > factors;
    factors.push_back(coeffs_);

    for(int k = 1; k < v.size(); ++k)
    {
        vector< vector<int> > fs(factors);
        for(auto i = fs.begin(); i != fs.end(); ++i)
        {
            vector<int>& f = *i;
            int s = 0;

            while(s < 2)
            {
                vector<int> g = sub_ground(v[k], s);
                vector<int> h = gcd(f, g);

                if(h != vector<int>({1}) && h != f)
                {
                    for(auto j = factors.begin(); j != factors.end(); ++j)
                    {
                        if(*j == f)
                        {
                            factors.erase(j);
                            break;
                        }
                    }

                    f = quotient(f, h);
                    factors.push_back(f);
                    factors.push_back(h);
                }

                if(factors.size() == v.size())
                {
                    return polynomials(factors);
                }
                ++s;
            }
        }
    }

    return polynomials(factors);
}

vector<Polynomial> Polynomial::polynomials(const vector< vector<int> >& fs)
{
    vector<Polynomial> r;
    for(int i = 0; i < fs.size(); ++i)
    {
        r.push_back(Polynomial(fs[i]));
    }
    return r;
}

vector<int> Polynomial::sub_ground(const vector<int>& f, int a)
{
    if(f != vector<int>({0}))
    {
        a ^= f[f.size()-1];
        if(degree(f) > 0)
        {
            vector<int> r(f.begin(), f.end()-1);
            r.push_back(a);
            return r;
        }
    }

    if(a==0)
    {
        return { 0 };
    }
    else
    {
        return { a };
    }
}

vector< vector<int> > Polynomial::berlekamp_qmatrix(const vector<int>& f)
{
    int n = degree(f);
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
        qq.push_back(c * (f[f.size()-1]));

        for(int j = 1; j < n; ++j)
        {
            qq.push_back(q[j-1] ^ c * (f[f.size()-1-j] & 1));
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
    int n = qmatrix.size();

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

        if(i == n)
        {
            continue;
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
