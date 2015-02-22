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

private:
    static unsigned int derivative(unsigned int n);
    static unsigned int multiply(unsigned int n, unsigned int m);
    static unsigned int lead(unsigned int n);
    static unsigned int quotient(unsigned int dividend, unsigned int divisor);
    static unsigned int remainder(unsigned int dividend, unsigned int divisor);
    static unsigned int gcd(unsigned int a, unsigned int b);

    unsigned int coeffs_;

};

#endif