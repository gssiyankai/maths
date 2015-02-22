#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <vector>
#include <string>

class Polynomial
{

public:
    Polynomial(const std::string& value);
    Polynomial(unsigned int coeffs);

    bool operator ==(const Polynomial& o) const;
    unsigned int coeffs() const;
    std::string str() const;
    Polynomial derivative() const;
    Polynomial multiply(const Polynomial& m) const;
    std::vector<Polynomial> divide(const Polynomial& divisor) const;
    Polynomial gcd(const Polynomial& p) const;
    std::vector<Polynomial> factorize() const;
    std::vector< std::pair<Polynomial, Polynomial> > pair_factorize(unsigned int d=0xFFFFFFFF) const;

private:
    static unsigned int derivative(unsigned int n);
    static unsigned int multiply(unsigned int n, unsigned int m);
    static unsigned int degree(unsigned int n);
    static unsigned int quotient(unsigned int dividend, unsigned int divisor);
    static unsigned int remainder(unsigned int dividend, unsigned int divisor);
    static unsigned int gcd(unsigned int a, unsigned int b);
    static unsigned int pow2(unsigned int n);
    static Polynomial multiply(const std::vector<Polynomial>& ps);

    unsigned int coeffs_;

};

#endif
