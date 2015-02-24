#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <vector>
#include <string>

class Polynomial
{

public:
    Polynomial(const std::string& value);
    Polynomial(std::vector<int> coeffs);

    bool operator ==(const Polynomial& o) const;
    std::vector<int> coeffs() const;
    std::string str() const;
    unsigned int degree() const;
    Polynomial multiply(const Polynomial& m) const;
    Polynomial gcd(const Polynomial& p) const;

//    std::vector<Polynomial> factorize_berlekamp() const;
//    static std::vector< std::vector<int> > berlekamp_qmatrix(unsigned int f);
//    static std::vector< std::vector<int> > berlekamp_qbasis(const std::vector< std::vector<int> >& qmatrix);
//    static unsigned int sub_ground(unsigned int f, unsigned int a);

private:
    static std::vector<int> strip(const std::vector<int>& n);
    static unsigned int degree(const std::vector<int>& n);
    static std::vector<int> multiply(const std::vector<int>& n, const std::vector<int>& m);
    static std::vector<int> gcd(std::vector<int> f, std::vector<int> g);
    static std::vector< std::vector<int> > divide(const std::vector<int>& f, const std::vector<int>& g);
    static std::vector<int> quotient(const std::vector<int>& f, const std::vector<int>& g);
    static std::vector<int> remainder(const std::vector<int>& f, const std::vector<int>& g);

    std::vector<int> coeffs_;

};

#endif
