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
//    Polynomial multiply(const Polynomial& m) const;
//    Polynomial gcd(const Polynomial& p) const;
//    std::vector<Polynomial> factorize_berlekamp() const;
//    static std::vector< std::vector<int> > berlekamp_qmatrix(unsigned int f);
//    static std::vector< std::vector<int> > berlekamp_qbasis(const std::vector< std::vector<int> >& qmatrix);
//    static unsigned int sub_ground(unsigned int f, unsigned int a);

private:
    static std::vector<int> strip(const std::vector<int>& cs);
//    static unsigned int multiply(unsigned int n, unsigned int m);
//    static unsigned int degree(unsigned int n);
//    static unsigned int quotient(unsigned int dividend, unsigned int divisor);
//    static unsigned int remainder(unsigned int dividend, unsigned int divisor);
//    static unsigned int gcd(unsigned int a, unsigned int b);

    std::vector<int> coeffs_;

};

#endif
